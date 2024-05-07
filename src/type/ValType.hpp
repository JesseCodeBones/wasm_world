#ifndef _wasm_type_
#define _wasm_type_
#include <any>
#include <cstdint>
#include <stdint.h>
// https://webassembly.github.io/spec/core/binary/types.html#binary-vectype

enum class ValType : uint8_t {

  // num type
  i32 = 0x7f,
  i64 = 0x7e,
  f32 = 0x7d,
  f64 = 0x7c,

  // vector type
  v128 = 0x7b,

  // reference type
  funcRef = 0x70,
  externRef = 0x6f,

};

typedef struct {
  ValType type;
  std::any value;
  bool multable;
} ValItem;
#endif