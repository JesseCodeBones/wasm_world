#include "./Module.hpp"
#include <algorithm>
#include <any>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "FunctionSec.hpp"
#include "ImportSec.hpp"
#include "TypeSec.hpp"
#include "instruction/CallInstruction.hpp"
#include "instruction/I32ConstInstruction.hpp"
#include "instruction/Instruction.hpp"
#include "reader/ModuleReader.hpp"
#include "runtime/Runtime.hpp"
#include "type/ImportDType.hpp"
void Module::dumpInfo() {
  std::cout << "------------------Module Info------------------" << std::endl;
}

void Module::checkImport() {
  // check if runtime has the capability to execute wasm
  for (auto &importItem : importSec) {
    switch (importItem.getType()) {
    case ImportDType::FUNC: {
      uint32_t functionIndex = importItem.getFunctionTypeIndex();
      assert(typeSec.size() > functionIndex);
      auto ifFound =
          std::find_if(runtime.getAPIs().begin(), runtime.getAPIs().end(),
                       [&](const API &api) {
                         return api.packageName == importItem.getPackage() &&
                                api.identifier == importItem.getIdentifier() &&
                                api.signature == typeSec.at(functionIndex);
                       });
      assert(ifFound != runtime.getAPIs().end());
      break;
    }
    default: {
      throw std::runtime_error("not implemented");
    }
    }
  }
}

void Module::execute() {
  runFunction(startIndex);
}

std::any Module::runFunction(uint32_t functionIndex) {
  // TODO handle parameter
  std::any result = nullptr;
  if (functionIndex >= importSec.size()) {
    // run internal function
    FunctionSec &function = functionSec.at(functionIndex - importSec.size());
    uint32_t functionReadPos = 0;
    // handle locals
    uint32_t localCount = ModuleReader::readUnsignedLEB128(
        function.localsAndExpression, functionReadPos);
    runExpression(function.localsAndExpression, functionReadPos);
  } else {
  }
  return result;
}

void Module::runExpression(std::vector<uint8_t> &body, uint32_t &position) {
  uint8_t opCode = ModuleReader::readUInt8(body, position);
  while (opCode != 0xb) { // end
    runInstruction(body, opCode, position);
    opCode = ModuleReader::readUInt8(body, position);
  }
}

void Module::runInstruction(std::vector<uint8_t> &body, uint8_t opcode,
                            uint32_t &position) {
  switch (opcode) {
  case (static_cast<uint32_t>(InstructionType::I32CONST)): {
    int32_t value = ModuleReader::readSignedLEB128(body, position);
    I32ConstInstruction instruction(value);
    instruction.fire(this);
    break;
  }
  case (static_cast<uint32_t>(InstructionType::CALL)): {
    uint32_t functionIndex = ModuleReader::readUnsignedLEB128(body, position);
    CallInstruction call(functionIndex);
    call.fire(this);
    break;
  }
  default: {
    throw std::runtime_error("not implemented");
  }
  }
}
