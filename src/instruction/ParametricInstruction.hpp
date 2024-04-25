#ifndef _wasm_parametric_instruction_
#define _wasm_parametric_instruction_
#include "../Module.hpp"
#include "Instruction.hpp"
class DropInstruction : public Instruction {
public:
  DropInstruction() {
    type = InstructionType::DROP;
  }
  void fire(void *module) {
    Module *ptr = (Module *)module;
    ptr->runtime.getStack().pop(); // simple drop one stack element
  }
};

#endif