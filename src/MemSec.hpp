#ifndef _wasm_memory_sec_
#define _wasm_memory_sec_
#include "AbstractSec.hpp"
#include "./type/LimitType.hpp"
#include <cstdint>
#include <vector>
class MemSec : public AbstractSec
{
private:
 LimitType limit;
public:
  MemSec(LimitType &&_limit):limit(_limit){}
  std::vector<uint8_t> memory;
};


#endif