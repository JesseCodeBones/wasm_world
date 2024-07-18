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
      break;
    }
    case InstructionType::I64_STORE: {
      int64_t value = valueStackItem.value.i64;
      auto memoryAddress = reinterpret_cast<int64_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::F32_STORE: {
      float value = valueStackItem.value.f32;
      auto memoryAddress = reinterpret_cast<float *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::F64_STORE: {
      double value = valueStackItem.value.f64;
      auto memoryAddress = reinterpret_cast<double *>(realAddress);
      *memoryAddress = value;
      break;
    }

    case InstructionType::I32_STORE8: {
      int8_t value = static_cast<int8_t>(valueStackItem.value.i32 & 0xFF);
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE8: {
      int8_t value = static_cast<int8_t>(valueStackItem.value.i64 & 0xFF);
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I32_STORE16: {
      int16_t value = static_cast<int16_t>(valueStackItem.value.i32 & 0xFFFF);
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE16: {
      int16_t value = static_cast<int16_t>(valueStackItem.value.i64 & 0xFFFF);
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      *memoryAddress = value;
      break;
    }
    case InstructionType::I64_STORE32: {
      int32_t value =
          static_cast<int32_t>(valueStackItem.value.i64 & 0xFFFFFFFF);
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
      break;
    }
    case InstructionType::I64_LOAD: {
      auto memoryAddress = reinterpret_cast<int64_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64, .value = {.i64 = *memoryAddress}});
      break;
    }
    case InstructionType::F32_LOAD: {
      auto memoryAddress = reinterpret_cast<float *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::f32, .value = {.f32 = *memoryAddress}});
      break;
    }
    case InstructionType::F64_LOAD: {
      auto memoryAddress = reinterpret_cast<double *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::f64, .value = {.f64 = *memoryAddress}});
      break;
    }
    case InstructionType::I32_LOAD8_S: {
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD8_U: {
      auto memoryAddress = reinterpret_cast<uint8_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD8_S: {
      auto memoryAddress = reinterpret_cast<int8_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD8_U: {
      auto memoryAddress = reinterpret_cast<uint8_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD16_S: {
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I32_LOAD16_U: {
      auto memoryAddress = reinterpret_cast<uint16_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD16_S: {
      auto memoryAddress = reinterpret_cast<int16_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD16_U: {
      auto memoryAddress = reinterpret_cast<uint16_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD32_S: {
      auto memoryAddress = reinterpret_cast<int32_t *>(realAddress);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(*memoryAddress)}});
      break;
    }
    case InstructionType::I64_LOAD32_U: {
      auto memoryAddress = reinterpret_cast<uint32_t *>(realAddress);
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
  default: {
    throw std::runtime_error("Invalid memory instruction");
  }
  }
}

uint32_t MemoryInstruction::calculateMemoryAddressWithOffsetAndAlign(
    uint32_t offset, uint32_t align, uint32_t base) {
  return ALIGN_UP(base + offset, align);
}
