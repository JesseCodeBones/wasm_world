#ifndef _wasm_control_instruction_
#define _wasm_control_instruction_
#include <cstdint>
#include "../Module.hpp"
#include "Instruction.hpp"
class ControlInstruction : public Instruction {
public:
  ControlInstruction(InstructionType _type);

  virtual void fire(void *module);
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

class BlockControlInstruction : public BlockInstruction {
public:
  BlockControlInstruction(InstructionType _type) : BlockInstruction() {
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

#endif