#ifndef _wasm_parametric_instruction_
#define _wasm_parametric_instruction_
#include <cstdint>
#include "../CompilerConstrant.hpp"
#include "../Module.hpp"
#include "Instruction.hpp"
class DropInstruction : public Instruction {
public:
  DropInstruction() {
    type = InstructionType::DROP;
  }
  void fire(void *module) {
    Module *ptr = (Module *)module;
    WASM_DEBUG("DROP\n");
    ptr->runtime.getStack()->pop(); // simple drop one stack element
  }
};

class SelectInstruction : public Instruction {
public:
  SelectInstruction() {
    type = InstructionType::SELECT;
  }
  void fire(void *module) {
    Module *ptr = (Module *)module;
    StackItem condition = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem param1 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    StackItem param2 = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    WASM_DEBUG("SELECT: " << static_cast<uint32_t>(condition.type) << "\n");
    switch (condition.type) {
    case ValType::i32: {
      if (condition.value.i32 == 0) {
        ptr->runtime.getStack()->push(std::move(param2));
      } else {
        ptr->runtime.getStack()->push(std::move(param1));
      }
      break;
    }
    case ValType::i64: {
      if (condition.value.i64 == 0) {
        ptr->runtime.getStack()->push(std::move(param2));
      } else {
        ptr->runtime.getStack()->push(std::move(param1));
      }
      break;
    }
    case ValType::f32: {
      if (condition.value.f32 == 0) {
        ptr->runtime.getStack()->push(std::move(param2));
      } else {
        ptr->runtime.getStack()->push(std::move(param1));
      }
      break;
    }
    case ValType::f64: {
      if (condition.value.f64 == 0) {
        ptr->runtime.getStack()->push(std::move(param2));
      } else {
        ptr->runtime.getStack()->push(std::move(param1));
      }
      break;
    }
    default: {
      throw std::runtime_error("unsupported stack type");
    }
    }
  }
};

#endif