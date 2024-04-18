#ifndef _wasm_type_sec_
#define _wasm_type_sec_
#include <vector>
#include "./type/ValType.hpp"
typedef struct {
  std::vector<ValType> parameters;
  std::vector<ValType> returns;
} TypeSec;

#endif