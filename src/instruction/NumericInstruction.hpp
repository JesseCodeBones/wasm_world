#ifndef _wasm_numeric_instruction_
#define _wasm_numeric_instruction_
#include <cassert>
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

class ComparationInstruction : public Instruction {
public:
  ComparationInstruction(InstructionType opcode) {
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

#endif