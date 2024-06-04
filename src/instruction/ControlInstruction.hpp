#ifndef _wasm_control_instruction_
#define _wasm_control_instruction_
#include "../Module.hpp"
#include "Instruction.hpp"
class ControlInstruction : public Instruction {
public:
  ControlInstruction(InstructionType _type);

  void fire(void *module);
};

#endif