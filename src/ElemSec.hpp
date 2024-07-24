#ifndef _wasm_elem_sec_
#define _wasm_elem_sec_
#include <cstdint>
class ElemSec {
private:
  uint32_t index;
  uint32_t value;

public:
  ElemSec(uint32_t index, uint32_t value) : index(index), value(value) {
  }
  uint32_t getIndex() {
    return index;
  }
  uint32_t getValue() {
    return value;
  }
  void setIndex(uint32_t index) {
    this->index = index;
  }
  void setValue(uint32_t value) {
    this->value = value;
  }
};

#endif