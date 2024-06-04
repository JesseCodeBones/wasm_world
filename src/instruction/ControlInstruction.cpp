#include "ControlInstruction.hpp"
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