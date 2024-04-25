#include "./Module.hpp"
#include <algorithm>
#include <any>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "FunctionSec.hpp"
#include "ImportSec.hpp"
#include "TypeSec.hpp"
#include "instruction/CallInstruction.hpp"
#include "instruction/Instruction.hpp"
#include "instruction/NumericInstruction.hpp"
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

std::unique_ptr<Instruction>
Module::compileInstruction(InstructionType opcode,
                           std::vector<uint8_t> &content, uint32_t &pos) {
  switch (opcode) {
  // 0x10
  case (InstructionType::CALL): {
    uint32_t functionIndex = ModuleReader::readUnsignedLEB128(content, pos);
    CallInstruction instruction(functionIndex);
    return std::make_unique<CallInstruction>(instruction);
  }

  // Numeric Instructions
  // 0x41
  case (InstructionType::I32CONST): {
    int32_t value = ModuleReader::readSignedLEB128(content, pos);
    I32ConstInstruction instruction(value);
    return std::make_unique<I32ConstInstruction>(instruction);
  }

  case (InstructionType::I64CONST): {
    int64_t value = ModuleReader::readSignedLEB128(content, pos);
    I64ConstInstruction instruction(value);
    return std::make_unique<I64ConstInstruction>(instruction);
  }

  case (InstructionType::F32CONST): {
    float value = ModuleReader::bit_cast<float>(
        ModuleReader::read4BytesLittleEndian(content, pos));
    F32ConstInstruction instruction(value);
    return std::make_unique<F32ConstInstruction>(instruction);
  }

  case (InstructionType::F64CONST): {
    double value = ModuleReader::bit_cast<double>(
        ModuleReader::read8BytesLittleEndian(content, pos));
    F64ConstInstruction instruction(value);
    return std::make_unique<F64ConstInstruction>(instruction);
  }

  default: {
    throw std::runtime_error("not implemented");
  }
  }
}

std::unique_ptr<std::vector<std::unique_ptr<Instruction>>>
Module::compileExpression(std::vector<uint8_t> &content, uint32_t &pos) {
  std::unique_ptr<std::vector<std::unique_ptr<Instruction>>> result =
      std::make_unique<std::vector<std::unique_ptr<Instruction>>>();
  InstructionType opCode =
      static_cast<InstructionType>(ModuleReader::readUInt8(content, pos));
  while (opCode != InstructionType::END) {
    result->push_back(compileInstruction(opCode, content, pos));
    opCode =
        static_cast<InstructionType>(ModuleReader::readUInt8(content, pos));
  }
  return std::move(result);
}

void Module::compileFunction(uint32_t functionIndex) {
  // TODO handle parameter
  assert(functionIndex >= importSec.size());
  FunctionSec &function = functionSec.at(functionIndex - importSec.size());
  uint32_t functionReadPos = 0;
  uint32_t localCount = ModuleReader::readUnsignedLEB128(
      function.localsAndExpression, functionReadPos);
  // TODO handle locals
  function.body =
      compileExpression(function.localsAndExpression, functionReadPos);
}

std::any Module::runFunction(uint32_t functionIndex) {
  // TODO handle parameter
  std::any result = nullptr;
  if (functionIndex >= importSec.size()) {
    // run internal function
    FunctionSec &function = functionSec.at(functionIndex - importSec.size());
    compileFunction(functionIndex);
    for (std::unique_ptr<Instruction> &instruction : *function.body) {
      instruction->fire(this);
    }
  } else {
  }
  return result;
}

// void Module::runExpression(std::vector<uint8_t> &body, uint32_t &position) {
//   uint8_t opCode = ModuleReader::readUInt8(body, position);
//   while (opCode != 0xb) { // end
//     runInstruction(body, opCode, position);
//     opCode = ModuleReader::readUInt8(body, position);
//   }
// }

// void Module::runInstruction(std::vector<uint8_t> &body, uint8_t opcode,
//                             uint32_t &position) {
//   switch (opcode) {
//   case (static_cast<uint32_t>(InstructionType::I32CONST)): {
//     int32_t value = ModuleReader::readSignedLEB128(body, position);
//     I32ConstInstruction instruction(value);
//     instruction.fire(this);
//     break;
//   }
//   case (static_cast<uint32_t>(InstructionType::CALL)): {
//     uint32_t functionIndex = ModuleReader::readUnsignedLEB128(body,
//     position); CallInstruction call(functionIndex); call.fire(this); break;
//   }
//   default: {
//     throw std::runtime_error("not implemented");
//   }
//   }
// }
