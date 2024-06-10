#include "ControlInstruction.hpp"
#include <cassert>
#include <stdexcept>
#include "Instruction.hpp"

ControlInstruction::ControlInstruction(InstructionType _type) {
  type = _type;
}

void ControlInstruction::fire(void *module) {
  Module *ptr = (Module *)module;

  switch (type) {

  case InstructionType::RETURN: {
    // return instruction handled in Module::runFunction body
    break;
  }
    // TODO handle other control instruction

  default: {
    throw std::runtime_error("invalid control instruction");
  }
  }
}

void IfInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  StackItem condition = ptr->runtime.getStack()->top();
  ptr->runtime.getStack()->pop();
  if (condition.value.i32 != 0) {
    for (auto &instruction : *thenInstructions) {
      instruction->fire(module);
    }
  } else {
    if (!elseInstructions->empty()) {
      for (auto &instruction : *elseInstructions) {
        instruction->fire(module);
      }
    }
  }
}
