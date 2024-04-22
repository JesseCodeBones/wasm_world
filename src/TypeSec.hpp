#ifndef _wasm_type_sec_
#define _wasm_type_sec_
#include <vector>
#include "./type/ValType.hpp"
typedef struct TypeSec {
  std::vector<ValType> parameters;
  std::vector<ValType> returns;

  bool operator==(const TypeSec &other) const {
    return parameters == other.parameters && returns == other.returns;
  }
} TypeSec;

#endif