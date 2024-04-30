#ifndef _wasm_variable_instruction_
#define _wasm_variable_instruction_

#include <any>
#include <cstdint>
#include "../Module.hpp"
#include "Instruction.hpp"
class LocalGetInstruction : public Instruction {

public:
  LocalGetInstruction(uint32_t _index) : index(_index) {
    type = InstructionType::LOCALGET;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    auto &local = ptr->internCallStack.back().locals.at(index);
    switch (local.type) {
    case ValType::i64: {
      int64_t value = std::any_cast<StackItemValue>(local.value).i64;
      StackItem stackItem = {ValType::i64, {.i64 = value}};
      ptr->runtime.getStack()->push(std::move(stackItem));
      break;
    }
    case ValType::f32: {
      float value = std::any_cast<StackItemValue>(local.value).f32;
      StackItem stackItem = {ValType::f32, {.f32 = value}};
      ptr->runtime.getStack()->push(std::move(stackItem));
      break;
    }
    case ValType::f64: {
      double value = std::any_cast<StackItemValue>(local.value).f64;
      StackItem stackItem = {ValType::f64, {.f64 = value}};
      ptr->runtime.getStack()->push(std::move(stackItem));
      break;
    }
    default: {
      // other type make as i32 type
      int32_t value = std::any_cast<StackItemValue>(local.value).i32;
      StackItem stackItem = {ValType::i32, {.i32 = value}};
      ptr->runtime.getStack()->push(std::move(stackItem));
      break;
    }
    }
  }

private:
  uint32_t index;
};

class LocalSetInstruction : public Instruction {
public:
  LocalSetInstruction(uint32_t _index) : index(_index) {
    type = InstructionType::LOCALSET;
  }
  void fire(void *module) {
    Module *ptr = (Module *)module;
    auto stackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    ptr->internCallStack.back().locals.at(index).value = stackItem.value;
  }

private:
  uint32_t index;
};

class LocalTeeInstruction : public Instruction {
public:
  LocalTeeInstruction(uint32_t _index) : index(_index) {
    type = InstructionType::LOCALTEE;
  }

  void fire(void *module) {
    Module *ptr = (Module *)module;
    auto stackItem = ptr->runtime.getStack()->top();
    // TEE use the value but not pop from the top
    ptr->internCallStack.back().locals.at(index).value = stackItem.value;
  }

private:
  uint32_t index;
};

#endif