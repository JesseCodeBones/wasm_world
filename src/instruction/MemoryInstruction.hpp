#ifndef _WASM_MEMORY_INSTRUCTION_
#define _WASM_MEMORY_INSTRUCTION_
#include <cstdint>
#include "Instruction.hpp"
class MemoryInstruction : public Instruction {
public:
  MemoryInstruction(InstructionType _type) {
    type = _type;
  }
  void fire(void *module) override;
  uint32_t memoryOffset = 0;
  uint32_t memoryAlign = 2;

private:
  static uint32_t calculateMemoryAddressWithOffsetAndAlign(uint32_t offset,
                                                           uint32_t align,
                                                           uint32_t base);
};
#endif