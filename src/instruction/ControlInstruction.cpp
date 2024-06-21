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

  case InstructionType::RETURN:
  case InstructionType::NOP: {
    // return instruction handled in Module::runFunction body
    break;
  }
  case InstructionType::UNREACHABLE: {
    assert(false);
  }
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

void LoopInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  ptr->runtime.addLoopBlock(this);
LOOP_LABEL:
  for (auto &instruction : *instructions) {
    instruction->fire(module);
    if (ptr->runtime.jumpToLoopBlockIndex > -1) {
      if (ptr->runtime.jumpToLoopBlockIndex == 0) {
        ptr->runtime.jumpToLoopBlockIndex = -1;
        goto LOOP_LABEL;
      } else {
        ptr->runtime.jumpToLoopBlockIndex--;
        break;
      }
    }
  }
  ptr->runtime.removeLoopBlock();
}

void BRIFInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  StackItem condition = ptr->runtime.getStack()->top();
  ptr->runtime.getStack()->pop();
  if (condition.value.i32 != 0) {
    ptr->runtime.jumpToLoopBlockIndex = targetIndex;
  }
}
