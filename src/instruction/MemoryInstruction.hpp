#ifndef _WASM_MEMORY_INSTRUCTION_
#define _WASM_MEMORY_INSTRUCTION_
#include <cstdint>
#include "Instruction.hpp"

/// memory.fill memory.copy data.drop memory.init instructions are not
/// implemented yet
class MemoryInstruction : public Instruction {
public:
  MemoryInstruction(InstructionType _type) {
    type = _type;
  }
  virtual void fire(void *module) override;
  uint32_t memoryOffset = 0;
  uint32_t memoryAlign = 2;

private:
  static uint32_t calculateMemoryAddressWithOffsetAndAlign(uint32_t offset,
                                                           uint32_t align,
                                                           uint32_t base);
};

enum class BulkSecondInstructionType : uint32_t {
  MEMORY_FILL = 11,
  MEMORY_COPY = 10,
  DATA_DROP = 9,
  MEMORY_INIT = 8
};

class BulkMemoryInstruction : public MemoryInstruction {
public:
  BulkMemoryInstruction(InstructionType _type) : MemoryInstruction(_type) {
  }
  BulkSecondInstructionType secondIndex;
  uint8_t u8_1;
  uint8_t u8_2;
  virtual void fire(void *module) override;
};

#endif