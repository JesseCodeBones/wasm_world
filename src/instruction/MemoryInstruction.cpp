#include "MemoryInstruction.hpp"
#include <cstdint>
#include <stdexcept>
#include "../Module.hpp"
#include "Instruction.hpp"
// address alignment
#define ALIGN_UP(x, align) (((x) + (align - 1)) & ~(align - 1))

void MemoryInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  switch (type) {
  case InstructionType::I32_STORE: {
    StackItem valueStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t value = valueStackItem.value.i32;
    StackItem positionStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t position = positionStackItem.value.i32;
    uint32_t address = calculateMemoryAddressWithOffsetAndAlign(
        memoryOffset, memoryAlign, position);
    auto realAddress = ptr->runtime.memoryPtr(address);
    auto uint32RealAddress = reinterpret_cast<uint32_t *>(realAddress);
    *uint32RealAddress = value;
    break;
  }
  case InstructionType::I32_LOAD: {
    StackItem positionStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t position = positionStackItem.value.i32;
    uint32_t address = calculateMemoryAddressWithOffsetAndAlign(
        memoryOffset, memoryAlign, position);
    auto realAddress = ptr->runtime.memoryPtr(address);
    auto uint32RealAddress = reinterpret_cast<int32_t *>(realAddress);
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = *uint32RealAddress}});
    break;
  }
  default: {
    throw std::runtime_error("Invalid memory instruction");
  }
  }
}

uint32_t MemoryInstruction::calculateMemoryAddressWithOffsetAndAlign(
    uint32_t offset, uint32_t align, uint32_t base) {
  return ALIGN_UP(base + offset, align);
}
