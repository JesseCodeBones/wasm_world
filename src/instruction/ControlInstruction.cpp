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
      if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
        ptr->runtime.jumpToLoopBlockIndex--;
        if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
          // if br target is not current block, break the block
          break;
        }
      }
    }
  } else {
    if (!elseInstructions->empty()) {
      for (auto &instruction : *elseInstructions) {
        instruction->fire(module);
        if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
          ptr->runtime.jumpToLoopBlockIndex--;
          if (ptr->runtime.jumpToLoopBlockIndex >= 0) {
            // if br target is not current block, break the block
            break;
          }
        }
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
  assert(static_cast<int32_t>(targetIndex) > -1);
  Module *ptr = (Module *)module;
  StackItem condition = ptr->runtime.getStack()->top();
  ptr->runtime.getStack()->pop();
  if (condition.value.i32 != 0) {
    ptr->runtime.jumpToLoopBlockIndex = targetIndex;
  }
}

void BRInstruction::fire(void *module) {
  assert(static_cast<int32_t>(targetIndex) > -1);
  Module *ptr = (Module *)module;
  ptr->runtime.jumpToLoopBlockIndex = targetIndex;
}

void BRTableInstruction::fire(void *module) {
  Module *ptr = (Module *)module;
  StackItem targetIndesStackItem = ptr->runtime.getStack()->top();
  ptr->runtime.getStack()->pop();
  uint32_t targetIndex = targetIndesStackItem.value.i32;
  if (targetIndex >= targetIndexs.size()) {
    ptr->runtime.jumpToLoopBlockIndex = defaultIndex;
  } else {
    ptr->runtime.jumpToLoopBlockIndex = targetIndexs[targetIndex];
  }
}
