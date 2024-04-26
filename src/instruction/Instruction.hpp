#ifndef _wasm_instruction_
#define _wasm_instruction_

#include <cstdint>
enum class InstructionType : uint8_t {

  NOP = 0x01,
  // Control Instructions
  CALL = 0x10,

  // Parametric Instructions
  DROP = 0x1a,
  SELECT = 0x1b,
  SELECTTYPE = 0x1c,

  // Variable Instructions
  LOCALGET = 0x20,
  LOCALSET = 0x21,
  LOCALTEE = 0x22,
  GLOBALGET = 0x23,
  GLOBALSET = 0x24,

  // Numeric Instructions
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