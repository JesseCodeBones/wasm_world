#ifndef _wasm_numeric_instruction_
#define _wasm_numeric_instruction_
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include "../Module.hpp"
#include "Instruction.hpp"
class I32ConstInstruction : public Instruction {
public:
  I32ConstInstruction(int32_t _value) : value(_value) {
    type = InstructionType::I32CONST;
  }
  inline int32_t getValue() {
    return value;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem stackItem = {ValType::i32, {(int32_t)value}};

    ptr->runtime.getStack()->push(stackItem);
  }

private:
  int32_t value;
};

class I64ConstInstruction : public Instruction {
public:
  I64ConstInstruction(int64_t _value) : value(_value) {
    type = InstructionType::I64CONST;
  }
  inline int64_t getValue() {
    return value;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem stackItem = {ValType::i64, {.i64 = (int64_t)value}};
    ptr->runtime.getStack()->push(stackItem);
  }

private:
  int64_t value;
};

class F32ConstInstruction : public Instruction {
public:
  F32ConstInstruction(float _value) : value(_value) {
    type = InstructionType::F32CONST;
  }
  inline float getValue() {
    return value;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem stackItem = {ValType::f32, {.f32 = value}};
    ptr->runtime.getStack()->push(stackItem);
  }

private:
  float value;
};

class F64ConstInstruction : public Instruction {
public:
  F64ConstInstruction(double _value) : value(_value) {
    type = InstructionType::F64CONST;
  }
  inline double getValue() {
    return value;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem stackItem = {ValType::f64, {.f64 = value}};
    ptr->runtime.getStack()->push(stackItem);
  }

private:
  double value;
};

class ComparisonInstruction : public Instruction {
public:
  ComparisonInstruction(InstructionType opcode) {
    this->type = static_cast<InstructionType>(opcode);
  }

  void fire(void *module) {
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
};

class NumericOperatorInstruction : public Instruction {
public:
  NumericOperatorInstruction(InstructionType _type) {
    type = _type;
  }

  void fire(void *module) {
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
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(result)}});
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
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(result)}});
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
          {.type = ValType::i64,
           .value = {.i64 = static_cast<int64_t>(result)}});
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
           .value = {.i32 = static_cast<int32_t>(std::rotl(
                         static_cast<uint32_t>(lhsStackItem.value.i32),
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
                         rhsStackItem.value.i64))}});

      break;
    }
    case InstructionType::I32ROTR: {
      StackItem rhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      StackItem lhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      ptr->runtime.getStack()->push(
          {.type = ValType::i32,
           .value = {.i32 = static_cast<int32_t>(std::rotr(
                         static_cast<uint32_t>(lhsStackItem.value.i32),
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
                         rhsStackItem.value.i64))}});
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
           .value = {.f32 = std::min(lhsStackItem.value.f32,
                                     rhsStackItem.value.f32)}});
      break;
    }

    case InstructionType::F64MIN: {
      StackItem rhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      StackItem lhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = std::min(lhsStackItem.value.f64,
                                     rhsStackItem.value.f64)}});
      break;
    }

    case InstructionType::F32MAX: {
      StackItem rhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      StackItem lhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      ptr->runtime.getStack()->push(
          {.type = ValType::f32,
           .value = {.f32 = std::max(lhsStackItem.value.f32,
                                     rhsStackItem.value.f32)}});
      break;
    }

    case InstructionType::F64MAX: {
      StackItem rhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      StackItem lhsStackItem = ptr->runtime.getStack()->top();
      ptr->runtime.getStack()->pop();
      ptr->runtime.getStack()->push(
          {.type = ValType::f64,
           .value = {.f64 = std::max(lhsStackItem.value.f64,
                                     rhsStackItem.value.f64)}});
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
          static_cast<int32_t>(f) > std::numeric_limits<uint32_t>::max()) {
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
      float f = rhsStackItem.value.f64;
      if (std::isnan(f) || f < 0 ||
          static_cast<int32_t>(f) > std::numeric_limits<uint32_t>::max()) {
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
          static_cast<int64_t>(f) > std::numeric_limits<uint64_t>::max()) {
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
      float f = rhsStackItem.value.f64;
      if (std::isnan(f) || f < 0 ||
          static_cast<int64_t>(f) > std::numeric_limits<uint64_t>::max()) {
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

    default: {
      throw std::runtime_error("unsupported numeric operator instruction");
    }
    }
  }
};

#endif