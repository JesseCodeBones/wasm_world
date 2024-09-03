#include "MemoryInstruction.hpp"
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include "../CompilerConstrant.hpp"
#include "../Module.hpp"
#include "Instruction.hpp"
// address alignment
#define ALIGN_UP(x, align) (((x) + (align - 1)) & ~(align - 1))

void MemoryInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  switch (type) {
  case InstructionType::I32_STORE:
  case InstructionType::I64_STORE:
  case InstructionType::F32_STORE:
  case InstructionType::F64_STORE:

  case InstructionType::I32_STORE8:
  case InstructionType::I32_STORE16:
  case InstructionType::I64_STORE8:
  case InstructionType::I64_STORE16:
  case InstructionType::I64_STORE32: {
    StackItem valueStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();

    StackItem positionStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t position = positionStackItem.value.i32;
    uint32_t address = calculateMemoryAddressWithOffsetAndAlign(
        memoryOffset, memoryAlign, position);
    auto realAddress = ptr->runtime.memoryPtr(address);
    switch (type) {
    case InstructionType::I32_STORE: {
      int32_t value = valueStackItem.value.i32;
      auto memoryAddress = reinterpret_cast<int32_t *>(realAddress);
      *memoryAddress = value;
      WASM_DEBUG("I32_STORE: " << value << " at " << address << "\n");
      break;
    }
    case InstructionType::I64_STORE: {
      int64_t value = valueStackItem.value.i64;
      WASM_DEBUG("I64_STORE: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int64_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::F32_STORE: {
      float value = valueStackItem.value.f32;
      WASM_DEBUG("F32_STORE: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<float *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::F64_STORE: {
      double value = valueStackItem.value.f64;
      WASM_DEBUG("F64_STORE: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<double *>(realAddress);
      *memoryAddress = value;
      break;
    }

    case InstructionType::I32_STORE8: {
      int8_t value = static_cast<int8_t>(valueStackItem.value.i32 & 0xFF);
      WASM_DEBUG("I32_STORE8: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE8: {
      int8_t value = static_cast<int8_t>(valueStackItem.value.i64 & 0xFF);
      WASM_DEBUG("I64_STORE8: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I32_STORE16: {
      int16_t value = static_cast<int16_t>(valueStackItem.value.i32 & 0xFFFF);
      WASM_DEBUG("I32_STORE16: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE16: {
      int16_t value = static_cast<int16_t>(valueStackItem.value.i64 & 0xFFFF);
      WASM_DEBUG("I64_STORE16: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE32: {
      int32_t value =
          static_cast<int32_t>(valueStackItem.value.i64 & 0xFFFFFFFF);
      WASM_DEBUG("I64_STORE32: " << value << " at " << address << "\n");
      auto memoryAddress = reinterpret_cast<int32_t *>(realAddress);
      *memoryAddress = value;
      break;
    }

    default: {
      throw std::runtime_error("Invalid memory store instruction");
    }
    }

    break;
  }
  case InstructionType::I32_LOAD:
  case InstructionType::I64_LOAD:
  case InstructionType::F32_LOAD:
  case InstructionType::F64_LOAD:
  case InstructionType::I32_LOAD8_S:
  case InstructionType::I32_LOAD8_U:
  case InstructionType::I32_LOAD16_S:
  case InstructionType::I32_LOAD16_U:
  case InstructionType::I64_LOAD8_S:
  case InstructionType::I64_LOAD8_U:
  case InstructionType::I64_LOAD16_S:
  case InstructionType::I64_LOAD16_U:
  case InstructionType::I64_LOAD32_S:
  case InstructionType::I64_LOAD32_U: {
    StackItem positionStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t position = positionStackItem.value.i32;
    uint32_t address = calculateMemoryAddressWithOffsetAndAlign(
        memoryOffset, memoryAlign, position);
    auto realAddress = ptr->runtime.memoryPtr(address);
    switch (type) {
    case InstructionType::I32_LOAD: {
      auto memoryAddress = reinterpret_cast<int32_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = *memoryAddress}});
      WASM_DEBUG("I32_LOAD: value " << *memoryAddress << " at " << address
                                    << "\n");
      break;
    }
    case InstructionType::I64_LOAD: {
      auto memoryAddress = reinterpret_cast<int64_t *>(realAddress);
      WASM_DEBUG("I64_LOAD: value " << *memoryAddress << " at " << address
                                    << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64, .value = {.i64 = *memoryAddress}});
      break;
    }
    case InstructionType::F32_LOAD: {
      auto memoryAddress = reinterpret_cast<float *>(realAddress);
      WASM_DEBUG("F32_LOAD: value " << *memoryAddress << " at " << address
                                    << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::f32, .value = {.f32 = *memoryAddress}});
      break;
    }
    case InstructionType::F64_LOAD: {
      auto memoryAddress = reinterpret_cast<double *>(realAddress);
      WASM_DEBUG("F64_LOAD: value " << *memoryAddress << " at " << address
                                    << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::f64, .value = {.f64 = *memoryAddress}});
      break;
    }
    case InstructionType::I32_LOAD8_S: {
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      WASM_DEBUG("I32_LOAD8_S: value " << *memoryAddress << " at " << address
                                       << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD8_U: {
      auto memoryAddress = reinterpret_cast<uint8_t *>(realAddress);
      WASM_DEBUG("I32_LOAD8_U: value " << *memoryAddress << " at " << address
                                       << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD8_S: {
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      WASM_DEBUG("I64_LOAD8_S: value " << *memoryAddress << " at " << address
                                       << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD8_U: {
      auto memoryAddress = reinterpret_cast<uint8_t *>(realAddress);
      WASM_DEBUG("I64_LOAD8_U: value " << *memoryAddress << " at " << address
                                       << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD16_S: {
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      WASM_DEBUG("I32_LOAD16_S: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD16_U: {
      auto memoryAddress = reinterpret_cast<uint16_t *>(realAddress);
      WASM_DEBUG("I32_LOAD16_U: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD16_S: {
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      WASM_DEBUG("I64_LOAD16_S: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD16_U: {
      auto memoryAddress = reinterpret_cast<uint16_t *>(realAddress);
      WASM_DEBUG("I64_LOAD16_U: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD32_S: {
      auto memoryAddress = reinterpret_cast<int32_t *>(realAddress);
      WASM_DEBUG("I64_LOAD32_S: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD32_U: {
      auto memoryAddress = reinterpret_cast<uint32_t *>(realAddress);
      WASM_DEBUG("I64_LOAD32_U: value " << *memoryAddress << " at " << address
                                        << "\n");
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    default: {
      throw std::runtime_error("Invalid memory load instruction");
    }
    }
    break;
  }
  case InstructionType::MEMORY_SIZE: {
    uint32_t memorySize = ptr->runtime.memorySize();
    WASM_DEBUG("MEMORY_SIZE: " << memorySize << "\n");
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(memorySize)}});
    break;
  }
  case InstructionType::MEMORY_GROW: {
    uint32_t memorySize = ptr->runtime.memorySize();
    StackItem growPageSize = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t pageSize = growPageSize.value.i32;
    WASM_DEBUG("MEMORY_GROW: " << pageSize << "\n");
    ptr->runtime.memoryGrow(static_cast<uint32_t>(pageSize));
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(memorySize)}});
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

void BulkMemoryInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  switch (secondIndex) {
  case BulkSecondInstructionType::MEMORY_FILL: {
    StackItem lengthStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem valueStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem positionStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t position = positionStackItem.value.i32;
    auto realAddress = static_cast<uint8_t *>(ptr->runtime.memoryPtr(position));
    uint32_t length = lengthStackItem.value.i32;
    uint8_t value = valueStackItem.value.i32 & 0xFF;
    WASM_DEBUG("MEMORY_FILL: " << value << " at " << position << " length "
                               << length << "\n");
    for (uint32_t i = 0; i < length; i++) {
      auto memoryAddress = reinterpret_cast<uint8_t *>(realAddress + i);
      *memoryAddress = value;
    }
    break;
  }
  case BulkSecondInstructionType::MEMORY_COPY: {
    StackItem lengthStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem sourceStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem destinationStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t destination = destinationStackItem.value.i32;
    int32_t source = sourceStackItem.value.i32;
    uint32_t length = lengthStackItem.value.i32;
    auto destinationAddress = ptr->runtime.memoryPtr(destination);
    auto sourceAddress = ptr->runtime.memoryPtr(source);
    WASM_DEBUG("MEMORY_COPY: " << source << " to " << destination << " length "
                               << length << "\n");
    std::memcpy(destinationAddress, sourceAddress, length);
    break;
  }
  default: {
    throw std::runtime_error("Invalid bulk memory instruction");
  }
  }
}
