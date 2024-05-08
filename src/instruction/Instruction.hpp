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
  //  -- numberic compare instruction
  I32EQZ = 0x45,  /* i32.eqz */
  I32EQ = 0x46,   /* i32.eq */
  I32NE = 0x47,   /* i32.ne */
  I32LT_S = 0x48, /* i32.lt_s */
  I32LT_U = 0x49, /* i32.lt_u */
  I32GT_S = 0x4a, /* i32.gt_s */
  I32GT_U = 0x4b, /* i32.gt_u */
  I32LE_S = 0x4c, /* i32.le_s */
  I32LE_U = 0x4d, /* i32.le_u */
  I32GE_S = 0x4e, /* i32.ge_s */
  I32GE_U = 0x4f, /* i32.ge_u */

  I64EQZ = 0x50,  /* i64.eqz */
  I64EQ = 0x51,   /* i64.eq */
  I64NE = 0x52,   /* i64.ne */
  I64LT_S = 0x53, /* i64.lt_s */
  I64LT_U = 0x54, /* i64.lt_u */
  I64GT_S = 0x55, /* i64.gt_s */
  I64GT_U = 0x56, /* i64.gt_u */
  I64LE_S = 0x57, /* i64.le_s */
  I64LE_U = 0x58, /* i64.le_u */
  I64GE_S = 0x59, /* i64.ge_s */
  I64GE_U = 0x5a, /* i64.ge_u */

  F32EQ = 0x5b, /* f32.eq */
  F32NE = 0x5c, /* f32.ne */
  F32LT = 0x5d, /* f32.lt */
  F32GT = 0x5e, /* f32.gt */
  F32LE = 0x5f, /* f32.le */
  F32GE = 0x60, /* f32.ge */

  F64EQ = 0x61, /* f64.eq */
  F64NE = 0x62, /* f64.ne */
  F64LT = 0x63, /* f64.lt */
  F64GT = 0x64, /* f64.gt */
  F64LE = 0x65, /* f64.le */
  F64GE = 0x66, /* f64.ge */

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