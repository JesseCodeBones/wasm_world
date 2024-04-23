#ifndef _wasm_i32_const_instruction_
#define _wasm_i32_const_instruction_
#include <cstdint>
#include "Instruction.hpp"
class I32ConstInstruction : public Instruction {
public:
  I32ConstInstruction(int32_t _value) : value(_value) {
    type = InstructionType::I32CONST;
  }
  inline int32_t getValue() {
    return value;
  }

  void fire(Module *module) {
    module->runtime.getStack().push(static_cast<int32_t>(value));
  }

private:
  int32_t value;
};

#endif