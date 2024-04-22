#ifndef _wasm_end_instruction_
#define _wasm_end_instruction_

#include "Instruction.hpp"
class EndInstruction : public Instruction {
public:
  EndInstruction() {
    type = InstructionType::END;
  }
};

#endif