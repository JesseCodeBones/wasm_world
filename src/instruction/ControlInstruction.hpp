#ifndef _wasm_control_instruction_
#define _wasm_control_instruction_
#include "../Module.hpp"
#include "Instruction.hpp"
class ControlInstruction : public Instruction {
public:
  ControlInstruction(InstructionType _type);

  virtual void fire(void *module);
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