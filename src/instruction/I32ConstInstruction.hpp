#ifndef _wasm_i32_const_instruction_
#define _wasm_i32_const_instruction_
#include <cstdint>
#include "../Module.hpp"
#include "Instruction.hpp"
class I32ConstInstruction : public Instruction {
public:
  I32ConstInstruction(int32_t _value) : value(_value) {
    type = InstructionType::I32CONST;
  }
  inline int32_t getValue() {
    return value;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem stackItem = {ValType::i32, {(int32_t)value}};

    ptr->runtime.getStack().push(stackItem);
  }

private:
  int32_t value;
};

#endif