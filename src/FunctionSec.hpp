#ifndef _wasm_function_sec_
#define _wasm_function_sec_
#include <cstdint>
#include <vector>
#include "TypeSec.hpp"
class FunctionSec {
private:
public:
  std::vector<uint8_t> localsAndExpression;
  TypeSec type;
};

#endif