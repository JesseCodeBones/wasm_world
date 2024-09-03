#include "NumericInstruction.hpp"
#include <algorithm>
#include <bit>
#include <cstdint>
#include <stdexcept>
void NumericOperatorInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  // first one is RHS
  // second one is LHS
  switch (type) {
  case InstructionType::I32CLZ: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i32);
    int32_t value = rhsStackItem.value.i32;
    int32_t result = std::countl_zero(static_cast<uint32_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = result}});
    break;
  }
  case InstructionType::I64CLZ: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i64);
    int64_t value = rhsStackItem.value.i64;
    int32_t result = std::countl_zero(static_cast<uint64_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i64, .value = {.i64 = static_cast<int64_t>(result)}});
    break;
  }
  case InstructionType::I32CTZ: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i32);
    int32_t value = rhsStackItem.value.i32;
    int32_t result = std::countr_zero(static_cast<uint32_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = result}});
    break;
  }
  case InstructionType::I64CTZ: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i64);
    int64_t value = rhsStackItem.value.i64;
    int32_t result = std::countr_zero(static_cast<uint64_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i64, .value = {.i64 = static_cast<int64_t>(result)}});
    break;
  }
  case InstructionType::I32POPCNT: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i32);
    int32_t value = rhsStackItem.value.i32;
    int32_t result = std::popcount(static_cast<uint32_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = result}});
    break;
  }
  case InstructionType::I64POPCNT: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(rhsStackItem.type == ValType::i64);
    int64_t value = rhsStackItem.value.i64;
    int32_t result = std::popcount(static_cast<uint64_t>(value));
    ptr->runtime.getStack()->push(
        {.type = ValType::i64, .value = {.i64 = static_cast<int64_t>(result)}});
    break;
  }

  case InstructionType::I32ADD:
  case InstructionType::I64ADD:
  case InstructionType::F32ADD:
  case InstructionType::F64ADD: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::I32ADD: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 =
                         (lhsStackItem.value.i32 + rhsStackItem.value.i32)}});
      break;
    }
    case InstructionType::I64ADD: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 =
                         (lhsStackItem.value.i64 + rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::F32ADD: {
      assert(lhsStackItem.type == ValType::f32);
      assert(rhsStackItem.type == ValType::f32);
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 =
                         (lhsStackItem.value.f32 + rhsStackItem.value.f32)}});
      break;
    }
    case InstructionType::F64ADD: {
      assert(lhsStackItem.type == ValType::f64);
      assert(rhsStackItem.type == ValType::f64);
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 =
                         (lhsStackItem.value.f64 + rhsStackItem.value.f64)}});
      break;
    }
    default: {
      assert(false); // directly exit
    }
    }
    break;
  }

  case InstructionType::I32SUB:
  case InstructionType::I64SUB:
  case InstructionType::F32SUB:
  case InstructionType::F64SUB: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::I32SUB: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 =
                         (lhsStackItem.value.i32 - rhsStackItem.value.i32)}});
      break;
    }
    case InstructionType::I64SUB: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 =
                         (lhsStackItem.value.i64 - rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::F32SUB: {
      assert(lhsStackItem.type == ValType::f32);
      assert(rhsStackItem.type == ValType::f32);
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 =
                         (lhsStackItem.value.f32 - rhsStackItem.value.f32)}});
      break;
    }
    case InstructionType::F64SUB: {
      assert(lhsStackItem.type == ValType::f64);
      assert(rhsStackItem.type == ValType::f64);
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 =
                         (lhsStackItem.value.f64 - rhsStackItem.value.f64)}});
      break;
    }
    default: {
      assert(false); // directly exit
    }
    }
    break;
  }

  case InstructionType::I32MUL:
  case InstructionType::I64MUL:
  case InstructionType::F32MUL:
  case InstructionType::F64MUL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::I32MUL: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 =
                         (lhsStackItem.value.i32 * rhsStackItem.value.i32)}});
      break;
    }
    case InstructionType::I64MUL: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 =
                         (lhsStackItem.value.i64 * rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::F32MUL: {
      assert(lhsStackItem.type == ValType::f32);
      assert(rhsStackItem.type == ValType::f32);
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 =
                         (lhsStackItem.value.f32 * rhsStackItem.value.f32)}});
      break;
    }
    case InstructionType::F64MUL: {
      assert(lhsStackItem.type == ValType::f64);
      assert(rhsStackItem.type == ValType::f64);
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 =
                         (lhsStackItem.value.f64 * rhsStackItem.value.f64)}});
      break;
    }
    default: {
      assert(false); // directly exit
    }
    }
    break;
  }

  case InstructionType::I32DIV_S:
  case InstructionType::I32DIV_U:
  case InstructionType::I64DIV_S:
  case InstructionType::I64DIV_U:
  case InstructionType::F32DIV:
  case InstructionType::F64DIV: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::I32DIV_S: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = (static_cast<int32_t>(lhsStackItem.value.i32 /
                                                  rhsStackItem.value.i32))}});
      break;
    }
    case InstructionType::I32DIV_U: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(
                         (static_cast<uint32_t>(lhsStackItem.value.i32) /
                          static_cast<uint32_t>(rhsStackItem.value.i32)))}});
      break;
    }
    case InstructionType::I64DIV_S: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(lhsStackItem.value.i64 /
                                                 rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::I64DIV_U: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(
                         static_cast<uint64_t>(lhsStackItem.value.i64) /
                         static_cast<uint64_t>(rhsStackItem.value.i64))}});
      break;
    }
    case InstructionType::F32DIV: {
      assert(lhsStackItem.type == ValType::f32);
      assert(rhsStackItem.type == ValType::f32);
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 =
                         (lhsStackItem.value.f32 / rhsStackItem.value.f32)}});
      break;
    }
    case InstructionType::F64DIV: {
      assert(lhsStackItem.type == ValType::f64);
      assert(rhsStackItem.type == ValType::f64);
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 =
                         (lhsStackItem.value.f64 / rhsStackItem.value.f64)}});
      break;
    }
    default: {
      assert(false); // directly exit
    }
    }
    break;
  }

  case InstructionType::I32REM_S:
  case InstructionType::I32REM_U:
  case InstructionType::I64REM_S:
  case InstructionType::I64REM_U: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::I32REM_S: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = (static_cast<int32_t>(lhsStackItem.value.i32 %
                                                  rhsStackItem.value.i32))}});
      break;
    }
    case InstructionType::I32REM_U: {
      assert(lhsStackItem.type == ValType::i32);
      assert(rhsStackItem.type == ValType::i32);
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(
                         (static_cast<uint32_t>(lhsStackItem.value.i32) %
                          static_cast<uint32_t>(rhsStackItem.value.i32)))}});
      break;
    }
    case InstructionType::I64REM_S: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(lhsStackItem.value.i64 %
                                                 rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::I64REM_U: {
      assert(lhsStackItem.type == ValType::i64);
      assert(rhsStackItem.type == ValType::i64);
      ptr->runtime.getStack()->push(
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(
                         static_cast<uint64_t>(lhsStackItem.value.i64) %
                         static_cast<uint64_t>(rhsStackItem.value.i64))}});
      break;
    }
    default: {
      assert(false); // directly exit
    }
    }
    break;
  }
  case InstructionType::I32AND: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (static_cast<uint32_t>(lhsStackItem.value.i32) &
                        static_cast<uint32_t>(rhsStackItem.value.i32)))}});
    break;
  }
  case InstructionType::I64AND: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (static_cast<uint64_t>(lhsStackItem.value.i64) &
                        static_cast<uint64_t>(rhsStackItem.value.i64)))}});
    break;
  }

  case InstructionType::I32OR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (static_cast<uint32_t>(lhsStackItem.value.i32) |
                        static_cast<uint32_t>(rhsStackItem.value.i32)))}});
    break;
  }
  case InstructionType::I64OR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (static_cast<uint64_t>(lhsStackItem.value.i64) |
                        static_cast<uint64_t>(rhsStackItem.value.i64)))}});
    break;
  }

  case InstructionType::I32XOR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (static_cast<uint32_t>(lhsStackItem.value.i32) ^
                        static_cast<uint32_t>(rhsStackItem.value.i32)))}});
    break;
  }
  case InstructionType::I64XOR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (static_cast<uint64_t>(lhsStackItem.value.i64) ^
                        static_cast<uint64_t>(rhsStackItem.value.i64)))}});
    break;
  }

  case InstructionType::I32SHL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (static_cast<uint32_t>(lhsStackItem.value.i32)
                        << static_cast<uint32_t>(rhsStackItem.value.i32)))}});
    break;
  }
  case InstructionType::I64SHL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (static_cast<uint64_t>(lhsStackItem.value.i64)
                        << static_cast<uint64_t>(rhsStackItem.value.i64)))}});
    break;
  }

  case InstructionType::I32SHR_S: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (lhsStackItem.value.i32 >> rhsStackItem.value.i32))}});
    break;
  }
  case InstructionType::I64SHR_S: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (lhsStackItem.value.i64 >> rhsStackItem.value.i64))}});
    break;
  }

  case InstructionType::I32SHR_U: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       (static_cast<uint32_t>(lhsStackItem.value.i32) >>
                        rhsStackItem.value.i32))}});
    break;
  }
  case InstructionType::I64SHR_U: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       (static_cast<uint64_t>(lhsStackItem.value.i64) >>
                        rhsStackItem.value.i64))}});
    break;
  }

  case InstructionType::I32ROTL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       std::rotl(static_cast<uint32_t>(lhsStackItem.value.i32),
                                 rhsStackItem.value.i32))}});
    break;
  }
  case InstructionType::I64ROTL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(std::rotl(
                       static_cast<uint64_t>(lhsStackItem.value.i64),
                       static_cast<int32_t>(rhsStackItem.value.i64)))}});

    break;
  }
  case InstructionType::I32ROTR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(
                       std::rotr(static_cast<uint32_t>(lhsStackItem.value.i32),
                                 rhsStackItem.value.i32))}});
    break;
  }
  case InstructionType::I64ROTR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(std::rotr(
                       static_cast<uint64_t>(lhsStackItem.value.i64),
                       static_cast<int32_t>(rhsStackItem.value.i64)))}});
    break;
  }

  case InstructionType::F32ABS: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::fabs(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64ABS: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::fabs(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32NEG: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32, .value = {.f32 = -rhsStackItem.value.f32}});
    break;
  }

  case InstructionType::F64NEG: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64, .value = {.f64 = -rhsStackItem.value.f64}});
    break;
  }

  case InstructionType::F32CEIL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::ceil(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64CEIL: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::ceil(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32FLOOR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::floor(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64FLOOR: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::floor(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32TRUNC: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::trunc(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64TRUNC: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::trunc(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32NEAREST: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::round(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64NEAREST: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::round(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32SQRT: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::sqrt(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64SQRT: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::sqrt(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32MIN: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {
             .f32 = std::min(lhsStackItem.value.f32, rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64MIN: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {
             .f64 = std::min(lhsStackItem.value.f64, rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32MAX: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {
             .f32 = std::max(lhsStackItem.value.f32, rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64MAX: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {
             .f64 = std::max(lhsStackItem.value.f64, rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F32COPYSIGN: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = std::copysign(lhsStackItem.value.f32,
                                        rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::F64COPYSIGN: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem lhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = std::copysign(lhsStackItem.value.f64,
                                        rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::I32WRAP_I64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(rhsStackItem.value.i64)}});
    break;
  }

  case InstructionType::I32TRUNC_S_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::I32TRUNC_U_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    float f = rhsStackItem.value.f32;
    if (std::isnan(f) || f < 0 ||
        f > static_cast<float>(std::numeric_limits<uint32_t>::max())) {
      throw std::runtime_error(
          "I32TRUNC_U_F32 ERROR, the imput f32 cannot be truncated!");
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::I32TRUNC_S_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::I32TRUNC_U_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    double f = rhsStackItem.value.f64;
    if (std::isnan(f) || f < 0 ||
        f > static_cast<double>(std::numeric_limits<uint32_t>::max())) {
      throw std::runtime_error(
          "I32TRUNC_U_F64 ERROR, the imput f64 cannot be truncated!");
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i32,
         .value = {.i32 = static_cast<int32_t>(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::I64TRUNC_S_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::I64TRUNC_U_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    float f = rhsStackItem.value.f32;
    if (std::isnan(f) || f < 0 ||
        f > static_cast<float>(std::numeric_limits<uint64_t>::max())) {
      throw std::runtime_error(
          "I64TRUNC_U_F32 ERROR, the imput f32 cannot be truncated!");
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(rhsStackItem.value.f32)}});
    break;
  }

  case InstructionType::I64TRUNC_S_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::I64TRUNC_U_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    double f = rhsStackItem.value.f64;
    if (std::isnan(f) || f < 0 ||
        f > static_cast<double>(std::numeric_limits<uint64_t>::max())) {
      throw std::runtime_error(
          "I64TRUNC_U_F64 ERROR, the imput f64 cannot be truncated!");
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::I64EXTEND_S_I32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(rhsStackItem.value.i32)}});
    break;
  }

  case InstructionType::I64EXTEND_U_I32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::i64,
         .value = {.i64 = static_cast<int64_t>(
                       static_cast<uint32_t>(rhsStackItem.value.i32))}});
    break;
  }

  case InstructionType::F32DEMOTE_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f32,
         .value = {.f32 = static_cast<float>(rhsStackItem.value.f64)}});
    break;
  }

  case InstructionType::F64PROMOTE_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->runtime.getStack()->push(
        {.type = ValType::f64,
         .value = {.f64 = static_cast<double>(rhsStackItem.value.f32)}});
    break;
  }

    // convert part
  case InstructionType::F32CONVERT_S_I32:
  case InstructionType::F32CONVERT_U_I32:
  case InstructionType::F32CONVERT_S_I64:
  case InstructionType::F32CONVERT_U_I64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::F32CONVERT_S_I32: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 = static_cast<float>(rhsStackItem.value.i32)}});
      break;
    }
    case InstructionType::F32CONVERT_U_I32: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 = static_cast<float>(
                         static_cast<uint32_t>(rhsStackItem.value.i32))}});
      break;
    }
    case InstructionType::F32CONVERT_S_I64: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 = static_cast<float>(rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::F32CONVERT_U_I64: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 = static_cast<float>(
                         static_cast<uint64_t>(rhsStackItem.value.i64))}});
      break;
    }
    default: {
      throw std::runtime_error("invalid f32 convert type");
      break;
    }
    }

    break;
  }

  case InstructionType::F64CONVERT_S_I32:
  case InstructionType::F64CONVERT_U_I32:
  case InstructionType::F64CONVERT_S_I64:
  case InstructionType::F64CONVERT_U_I64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    switch (type) {
    case InstructionType::F64CONVERT_S_I32: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = static_cast<double>(rhsStackItem.value.i32)}});
      break;
    }
    case InstructionType::F64CONVERT_U_I32: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = static_cast<double>(
                         static_cast<uint32_t>(rhsStackItem.value.i32))}});
      break;
    }
    case InstructionType::F64CONVERT_S_I64: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = static_cast<double>(rhsStackItem.value.i64)}});
      break;
    }
    case InstructionType::F64CONVERT_U_I64: {
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = static_cast<double>(
                         static_cast<uint64_t>(rhsStackItem.value.i64))}});
      break;
    }
    default: {
      throw std::runtime_error("invalid F64 convert type");
      break;
    }
    }

    break;
  }

  case InstructionType::I32REINTERPRET_F32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t temValue;
    std::memcpy(&temValue, &rhsStackItem.value.f32, sizeof(int32_t));
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = temValue}});
    break;
  }

  case InstructionType::I64REINTERPRET_F64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int64_t temValue;
    std::memcpy(&temValue, &rhsStackItem.value.f64, sizeof(int64_t));
    ptr->runtime.getStack()->push(
        {.type = ValType::i64, .value = {.i64 = temValue}});
    break;
  }

  case InstructionType::F32REINTERPRET_I32: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    float temValue;
    std::memcpy(&temValue, &rhsStackItem.value.i32, sizeof(float));
    ptr->runtime.getStack()->push(
        {.type = ValType::f32, .value = {.f32 = temValue}});
    break;
  }

  case InstructionType::F64REINTERPRET_I64: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    double temValue;
    std::memcpy(&temValue, &rhsStackItem.value.i64, sizeof(double));
    ptr->runtime.getStack()->push(
        {.type = ValType::f64, .value = {.f64 = temValue}});
    break;
  }

  case InstructionType::I32EXTEND8_S:
  case InstructionType::I32EXTEND16_S: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int32_t temValue;
    switch (type) {
    case InstructionType::I32EXTEND8_S: {
      temValue =
          static_cast<int32_t>(static_cast<int8_t>(rhsStackItem.value.i32));
      break;
    }
    case InstructionType::I32EXTEND16_S: {
      temValue =
          static_cast<int32_t>(static_cast<int16_t>(rhsStackItem.value.i32));
      break;
    }
    default: {
      throw std::runtime_error("invalid i32 extend with signal type");
      break;
    }
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i32, .value = {.i32 = temValue}});
    break;
  }

  case InstructionType::I64EXTEND8_S:
  case InstructionType::I64EXTEND16_S:
  case InstructionType::I64EXTEND32_S: {
    StackItem rhsStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    int64_t temValue;
    switch (type) {
    case InstructionType::I64EXTEND8_S: {
      temValue =
          static_cast<int64_t>(static_cast<int8_t>(rhsStackItem.value.i64));
      break;
    }
    case InstructionType::I64EXTEND16_S: {
      temValue =
          static_cast<int64_t>(static_cast<int16_t>(rhsStackItem.value.i64));
      break;
    }
    case InstructionType::I64EXTEND32_S: {
      temValue =
          static_cast<int64_t>(static_cast<int32_t>(rhsStackItem.value.i64));
      break;
    }
    default: {
      throw std::runtime_error("invalid i64 extend with signal type");
      break;
    }
    }
    ptr->runtime.getStack()->push(
        {.type = ValType::i64, .value = {.i64 = temValue}});
    break;
  }

    // **ATENTION**
    // current compiler donot support saturating truncation instructions
  default: {
    throw std::runtime_error("unsupported numeric operator instruction");
  }
  }
}

void ComparisonInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  // first one is RHS
  // second one is LHS
  switch (type) {
  case InstructionType::I32EQZ: {
    StackItem stackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem.type == ValType::i32);
    int32_t value = stackItem.value.i32;
    if (value == 0) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64EQZ: {
    StackItem stackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem.type == ValType::i64);
    int64_t value = stackItem.value.i64;
    if (value == 0) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32EQ: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    WASM_DEBUG("I32EQ: " << stackItem1.value.i32 << " : "
                         << stackItem2.value.i32 << std::endl);
    if (stackItem1.value.i32 == stackItem2.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64EQ: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem1.value.i64 == stackItem2.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32EQ: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem1.value.f32 == stackItem2.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64EQ: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem1.value.f64 == stackItem2.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32NE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (stackItem1.value.i32 != stackItem2.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64NE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem1.value.i64 != stackItem2.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32NE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem1.value.f32 != stackItem2.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64NE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem1.value.f64 != stackItem2.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32LT_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (stackItem2.value.i32 < stackItem1.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32LT_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (static_cast<uint32_t>(stackItem2.value.i32) <
        static_cast<uint32_t>(stackItem1.value.i32)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64LT_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem2.value.i64 < stackItem1.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64LT_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (static_cast<uint64_t>(stackItem2.value.i64) <
        static_cast<uint64_t>(stackItem1.value.i64)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32LT: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem2.value.f32 < stackItem1.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64LT: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem2.value.f64 < stackItem1.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32GT_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (stackItem2.value.i32 > stackItem1.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32GT_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (static_cast<uint32_t>(stackItem2.value.i32) >
        static_cast<uint32_t>(stackItem1.value.i32)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64GT_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem2.value.i64 > stackItem1.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64GT_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (static_cast<uint64_t>(stackItem2.value.i64) >
        static_cast<uint64_t>(stackItem1.value.i64)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32GT: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem2.value.f32 > stackItem1.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64GT: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem2.value.f64 > stackItem1.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }

  case InstructionType::I32LE_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (stackItem2.value.i32 <= stackItem1.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32LE_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (static_cast<uint32_t>(stackItem2.value.i32) <=
        static_cast<uint32_t>(stackItem1.value.i32)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64LE_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem2.value.i64 <= stackItem1.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64LE_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (static_cast<uint64_t>(stackItem2.value.i64) <=
        static_cast<uint64_t>(stackItem1.value.i64)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32LE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem2.value.f32 <= stackItem1.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64LE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem2.value.f64 <= stackItem1.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }

  case InstructionType::I32GE_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (stackItem2.value.i32 >= stackItem1.value.i32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I32GE_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i32);
    if (static_cast<uint32_t>(stackItem2.value.i32) >=
        static_cast<uint32_t>(stackItem1.value.i32)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64GE_S: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (stackItem2.value.i64 >= stackItem1.value.i64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::I64GE_U: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::i64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::i64);
    if (static_cast<uint64_t>(stackItem2.value.i64) >=
        static_cast<uint64_t>(stackItem1.value.i64)) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F32GE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f32);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f32);
    if (stackItem2.value.f32 >= stackItem1.value.f32) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }
  case InstructionType::F64GE: {
    StackItem stackItem1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem1.type == ValType::f64);
    StackItem stackItem2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    assert(stackItem2.type == ValType::f64);
    if (stackItem2.value.f64 >= stackItem1.value.f64) {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 1}});
    } else {
      ptr->runtime.getStack()->push(
          {.type = ValType::i32, .value = {.i32 = 0}});
    }
    break;
  }

  default: {
    throw std::runtime_error("unsupported compare instruction");
  }
  }
}