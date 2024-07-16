#ifndef _wasm_memory_sec_
#define _wasm_memory_sec_
#include <cstdint>
#include <stdexcept>
#include <vector>
#include "./type/LimitType.hpp"
#include "AbstractSec.hpp"
class MemSec : public AbstractSec {
private:
  LimitType limit;

public:
  MemSec(LimitType &&_limit) : limit(_limit) {
    memory.resize(limit.min * 65536);
  }

  inline void setMemory(uint32_t memoryPos, std::vector<uint8_t> &source,
                        uint32_t start, uint32_t stop) {
    if (stop <= start) {
      throw std::runtime_error("invalid position");
    }
    if (limit.tag == 1 && limit.max != UINT32_MAX) {
      if (memoryPos + stop - start > limit.max * 65536) {
        throw std::runtime_error("memory set out of bounds");
      }
    }
    memory.insert(memory.begin() + memoryPos, source.begin() + start,
                  source.begin() + stop);
  }

  std::vector<uint8_t> memory;
};

#endif