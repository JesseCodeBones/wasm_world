#ifndef _wasm_i32_const_instruction_
#define _wasm_i32_const_instruction_
#include "Instruction.hpp"
#include <cstdint>
class I32ConstInstruction : public Instruction {
public:
  I32ConstInstruction(int32_t _value):value(_value) { type = InstructionType::I32CONST; }
  inline int32_t getValue(){return value;}

private:
  int32_t value;
};

#endif