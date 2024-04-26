#ifndef _wasm_numeric_instruction_
#define _wasm_numeric_instruction_
#include <cstdint>
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

#endif