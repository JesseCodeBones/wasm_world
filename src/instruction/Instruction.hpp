#ifndef _wasm_instruction_
#define _wasm_instruction_

#include <cstdint>
enum class InstructionType : uint8_t {

  NOP = 0x01,

  CALL = 0x10,

  I32CONST = 0x41,
  I64CONST = 0x42,
  F32CONST = 0x43,
  F64CONST = 0x44,

  END = 0x0B
};

class Instruction {
public:
  InstructionType type = InstructionType::NOP;
  template <typename T>
  T *castRef() {
    return static_cast<T *>(this);
  }

  template <typename T>
  T &&castRightRef() {
    return static_cast<T &&>(*this);
  }
  virtual void fire(void *module) = 0;
  virtual ~Instruction(){};
};

#endif