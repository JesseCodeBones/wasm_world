#ifndef _wasm_instruction_
#define _wasm_instruction_

#include <cstdint>
#include "../type/ValType.hpp"
enum class InstructionType : uint8_t {

  // Control Instructions
  UNREACHABLE = 0x00, /* unreachable */
  NOP = 0x01,
  BLOCK = 0x02,   /* block */
  LOOP = 0x03,    /* loop */
  IF = 0x04,      /* if */
  ELSE = 0x05,    /* else */
  TRY = 0x06,     /* try */
  CATCH = 0x07,   /* catch* */
  THROW = 0x08,   /* throw of a try catch */
  RETHROW = 0x09, /* rethrow of a try catch */
  UNUSED_0x0a = 0x0a,
  END = 0x0b,                  /* end */
  BR = 0x0c,                   /* br */
  BR_IF = 0x0d,                /* br if */
  BR_TABLE = 0x0e,             /* br table */
  RETURN = 0x0f,               /* return */
  CALL = 0x10,                 /* call */
  CALL_INDIRECT = 0x11,        /* call_indirect */
  RETURN_CALL = 0x12,          /* return_call */
  RETURN_CALL_INDIRECT = 0x13, /* return_call_indirect */
  CALL_REF = 0x14,             /* call_ref */
  RETURN_CALL_REF = 0x15,      /* return_call_ref */

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

  // numeric operators
  I32CLZ = 0x67,      /* i32.clz */
  I32CTZ = 0x68,      /* i32.ctz */
  I32POPCNT = 0x69,   /* i32.popcnt */
  I32ADD = 0x6a,      /* i32.add */
  I32SUB = 0x6b,      /* i32.sub */
  I32MUL = 0x6c,      /* i32.mul */
  I32DIV_S = 0x6d,    /* i32.div_s */
  I32DIV_U = 0x6e,    /* i32.div_u */
  I32REM_S = 0x6f,    /* i32.rem_s */
  I32REM_U = 0x70,    /* i32.rem_u */
  I32AND = 0x71,      /* i32.and */
  I32OR = 0x72,       /* i32.or */
  I32XOR = 0x73,      /* i32.xor */
  I32SHL = 0x74,      /* i32.shl */
  I32SHR_S = 0x75,    /* i32.shr_s */
  I32SHR_U = 0x76,    /* i32.shr_u */
  I32ROTL = 0x77,     /* i32.rotl */
  I32ROTR = 0x78,     /* i32.rotr */
  I64CLZ = 0x79,      /* i64.clz */
  I64CTZ = 0x7a,      /* i64.ctz */
  I64POPCNT = 0x7b,   /* i64.popcnt */
  I64ADD = 0x7c,      /* i64.add */
  I64SUB = 0x7d,      /* i64.sub */
  I64MUL = 0x7e,      /* i64.mul */
  I64DIV_S = 0x7f,    /* i64.div_s */
  I64DIV_U = 0x80,    /* i64.div_u */
  I64REM_S = 0x81,    /* i64.rem_s */
  I64REM_U = 0x82,    /* i64.rem_u */
  I64AND = 0x83,      /* i64.and */
  I64OR = 0x84,       /* i64.or */
  I64XOR = 0x85,      /* i64.xor */
  I64SHL = 0x86,      /* i64.shl */
  I64SHR_S = 0x87,    /* i64.shr_s */
  I64SHR_U = 0x88,    /* i64.shr_u */
  I64ROTL = 0x89,     /* i64.rotl */
  I64ROTR = 0x8a,     /* i64.rotr */
  F32ABS = 0x8b,      /* f32.abs */
  F32NEG = 0x8c,      /* f32.neg */
  F32CEIL = 0x8d,     /* f32.ceil */
  F32FLOOR = 0x8e,    /* f32.floor */
  F32TRUNC = 0x8f,    /* f32.trunc */
  F32NEAREST = 0x90,  /* f32.nearest */
  F32SQRT = 0x91,     /* f32.sqrt */
  F32ADD = 0x92,      /* f32.add */
  F32SUB = 0x93,      /* f32.sub */
  F32MUL = 0x94,      /* f32.mul */
  F32DIV = 0x95,      /* f32.div */
  F32MIN = 0x96,      /* f32.min */
  F32MAX = 0x97,      /* f32.max */
  F32COPYSIGN = 0x98, /* f32.copysign */
  F64ABS = 0x99,      /* f64.abs */
  F64NEG = 0x9a,      /* f64.neg */
  F64CEIL = 0x9b,     /* f64.ceil */
  F64FLOOR = 0x9c,    /* f64.floor */
  F64TRUNC = 0x9d,    /* f64.trunc */
  F64NEAREST = 0x9e,  /* f64.nearest */
  F64SQRT = 0x9f,     /* f64.sqrt */
  F64ADD = 0xa0,      /* f64.add */
  F64SUB = 0xa1,      /* f64.sub */
  F64MUL = 0xa2,      /* f64.mul */
  F64DIV = 0xa3,      /* f64.div */
  F64MIN = 0xa4,      /* f64.min */
  F64MAX = 0xa5,      /* f64.max */
  F64COPYSIGN = 0xa6, /* f64.copysign */

  /* conversions */
  I32WRAP_I64 = 0xa7,        /* i32.wrap/i64 */
  I32TRUNC_S_F32 = 0xa8,     /* i32.trunc_s/f32 */
  I32TRUNC_U_F32 = 0xa9,     /* i32.trunc_u/f32 */
  I32TRUNC_S_F64 = 0xaa,     /* i32.trunc_s/f64 */
  I32TRUNC_U_F64 = 0xab,     /* i32.trunc_u/f64 */
  I64EXTEND_S_I32 = 0xac,    /* i64.extend_s/i32 */
  I64EXTEND_U_I32 = 0xad,    /* i64.extend_u/i32 */
  I64TRUNC_S_F32 = 0xae,     /* i64.trunc_s/f32 */
  I64TRUNC_U_F32 = 0xaf,     /* i64.trunc_u/f32 */
  I64TRUNC_S_F64 = 0xb0,     /* i64.trunc_s/f64 */
  I64TRUNC_U_F64 = 0xb1,     /* i64.trunc_u/f64 */
  F32CONVERT_S_I32 = 0xb2,   /* f32.convert_s/i32 */
  F32CONVERT_U_I32 = 0xb3,   /* f32.convert_u/i32 */
  F32CONVERT_S_I64 = 0xb4,   /* f32.convert_s/i64 */
  F32CONVERT_U_I64 = 0xb5,   /* f32.convert_u/i64 */
  F32DEMOTE_F64 = 0xb6,      /* f32.demote/f64 */
  F64CONVERT_S_I32 = 0xb7,   /* f64.convert_s/i32 */
  F64CONVERT_U_I32 = 0xb8,   /* f64.convert_u/i32 */
  F64CONVERT_S_I64 = 0xb9,   /* f64.convert_s/i64 */
  F64CONVERT_U_I64 = 0xba,   /* f64.convert_u/i64 */
  F64PROMOTE_F32 = 0xbb,     /* f64.promote/f32 */
  I32REINTERPRET_F32 = 0xbc, /* i32.reinterpret/f32 */
  I64REINTERPRET_F64 = 0xbd, /* i64.reinterpret/f64 */
  F32REINTERPRET_I32 = 0xbe, /* f32.reinterpret/i32 */
  F64REINTERPRET_I64 = 0xbf, /* f64.reinterpret/i64 */
  I32EXTEND8_S = 0xc0,       /* i32.extend8_s */
  I32EXTEND16_S = 0xc1,      /* i32.extend16_s */
  I64EXTEND8_S = 0xc2,       /* i64.extend8_s */
  I64EXTEND16_S = 0xc3,      /* i64.extend16_s */
  I64EXTEND32_S = 0xc4,      /* i64.extend32_s */

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