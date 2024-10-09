#ifndef _wasm_numeric_instruction_
#define _wasm_numeric_instruction_

#ifdef __WIN32__
#define NOMINMAX
#include <algorithm>
#include <gdiplus.h>
#include <windows.h>
#endif

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>

#include "../CompilerConstrant.hpp"
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
    WASM_DEBUG("I32CONST: " << (int32_t)value << "\n");
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
    WASM_DEBUG("I64CONST: " << (int64_t)value << "\n");
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
    WASM_DEBUG("F32CONST: " << value << "\n");
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
    WASM_DEBUG("F64CONST: " << value << "\n");
    ptr->runtime.getStack()->push(stackItem);
  }

private:
  double value;
};

enum TruncSatNumberInstructionOpcode : uint8_t {
  I32_TRUNC_SAT_F32_S = 0x0,
  I32_TRUNC_SAT_F32_U = 0x1,
  I32_TRUNC_SAT_F64_S = 0x2,
  I32_TRUNC_SAT_F64_U = 0x3,
  I64_TRUNC_SAT_F32_S = 0x4,
  I64_TRUNC_SAT_F32_U = 0x5,
  I64_TRUNC_SAT_F64_S = 0x6,
  I64_TRUNC_SAT_F64_U = 0x7,
};

class TruncSatNumberInstruction : public Instruction {
public:
  TruncSatNumberInstruction(TruncSatNumberInstructionOpcode _opcode)
      : satOpcode(_opcode) {
    type = InstructionType::NOP;
  }
  void fire(void *module);

private:
  TruncSatNumberInstructionOpcode satOpcode;
};

class ComparisonInstruction : public Instruction {
public:
  ComparisonInstruction(InstructionType opcode) {
    this->type = static_cast<InstructionType>(opcode);
  }

  void fire(void *module);
};

class NumericOperatorInstruction : public Instruction {
public:
  NumericOperatorInstruction(InstructionType _type) {
    type = _type;
  }

  void fire(void *module);
};

#endif