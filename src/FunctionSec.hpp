#ifndef _wasm_function_sec_
#define _wasm_function_sec_
#include <cstdint>
#include <memory>
#include <vector>
#include "TypeSec.hpp"
#include "instruction/Instruction.hpp"

class FunctionSec {
private:
public:
  std::vector<uint8_t> localsAndExpression;
  TypeSec type;
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> body;
  std::vector<ValItem> locals;
  uint32_t paramSize;
};

#endif