#ifndef _wasm_control_instruction_
#define _wasm_control_instruction_
#include <cstdint>
#include "../CompilerConstrant.hpp"
#include "../Module.hpp"
#include "Instruction.hpp"
class ControlInstruction : public Instruction {
public:
  ControlInstruction(InstructionType _type);

  virtual void fire(void *module);
};

class BRTableInstruction : public ControlInstruction {
public:
  BRTableInstruction(InstructionType _type,
                     std::vector<uint32_t> &&_targetIndexs,
                     uint32_t _defaultIndex)
      : ControlInstruction(_type), targetIndexs(_targetIndexs),
        defaultIndex(_defaultIndex) {
  }
  void fire(void *module) override;

  std::vector<uint32_t> &getTargetIndexs() {
    return targetIndexs;
  }

  uint32_t getDefaultIndex() {
    return defaultIndex;
  }

private:
  std::vector<uint32_t> targetIndexs;
  uint32_t defaultIndex;
};

class BlockBaseInstruction : public Instruction {

private:
  ValType blockType;
  bool hasReturn = false;

public:
  BlockBaseInstruction() = default;

  bool getHasReturn() {
    return hasReturn;
  }
  void setHasReturn(bool _hasReturn) {
    hasReturn = _hasReturn;
  }
  ValType getBlockType() {
    return blockType;
  }
  void setBlockType(ValType _blockType) {
    blockType = _blockType;
  }
  virtual void fire(void *module) {};
};

class BRIFInstruction : public ControlInstruction {
public:
  BRIFInstruction(InstructionType _type, uint32_t _targetIndex)
      : ControlInstruction(_type), targetIndex(_targetIndex) {
  }
  void fire(void *module);

private:
  uint32_t targetIndex;
};

class BRInstruction : public ControlInstruction {
public:
  BRInstruction(InstructionType _type, uint32_t _targetIndex)
      : ControlInstruction(_type), targetIndex(_targetIndex) {
  }
  void fire(void *module);

private:
  uint32_t targetIndex;
};

class BlockControlInstruction : public BlockBaseInstruction {
public:
  BlockControlInstruction(InstructionType _type) : BlockBaseInstruction() {
    type = _type;
  }
  virtual void fire(void *module) = 0;
};

class IfInstruction : public BlockControlInstruction {
public:
  IfInstruction(InstructionType _type) : BlockControlInstruction(_type) {
    thenInstructions =
        std::make_unique<std::vector<std::unique_ptr<Instruction>>>();
    elseInstructions =
        std::make_unique<std::vector<std::unique_ptr<Instruction>>>();
  };
  void fire(void *module);
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> thenInstructions;
  ;
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> elseInstructions;
};

class LoopInstruction : public BlockControlInstruction {
public:
  LoopInstruction(InstructionType _type) : BlockControlInstruction(_type) {
    instructions =
        std::make_unique<std::vector<std::unique_ptr<Instruction>>>();
  };
  void fire(void *module);
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> instructions;
};

class BlockInstruction : public Instruction {
public:
  BlockInstruction() : Instruction() {
    instructions =
        std::make_unique<std::vector<std::unique_ptr<Instruction>>>();
  }
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> instructions;
  void fire(void *module) {
    Module *ptr = (Module *)module;
    WASM_DEBUG("block instruction\n");
    for (auto &instruction : *instructions) {
      instruction->fire(module);
      if (ptr->internCallStack.back().returnFlag) {
        break;
      }
      if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
        ptr->runtime.jumpToLoopBlockIndex--;
        if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
          // if br target is not current block, break the block
          break;
        }
      }
    }
  }
};

#endif