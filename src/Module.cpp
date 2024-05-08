#include "./Module.hpp"
#include <algorithm>
#include <any>
#include <cassert>
#include <cstddef>
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
#include "instruction/ParametricInstruction.hpp"
#include "instruction/VariableInstruction.hpp"
#include "reader/ModuleReader.hpp"
#include "runtime/Runtime.hpp"
#include "type/ImportDType.hpp"
#include "type/ValType.hpp"
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
  if (static_cast<uint32_t>(-1) == startIndex) {
    throw std::runtime_error("Module does not have start function");
  }
  runFunction(startIndex);
}

std::unique_ptr<Instruction>
Module::compileInstruction(InstructionType opcode,
                           std::vector<uint8_t> &content, uint32_t &pos) {
  switch (opcode) {
  // 0x10
  case (InstructionType::CALL): {
    uint32_t functionIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    CallInstruction instruction(functionIndex);
    return std::make_unique<CallInstruction>(instruction);
  }

  // Parametric Instructions
  case (InstructionType::DROP): {
    DropInstruction instruction;
    return std::make_unique<DropInstruction>(instruction);
  }
  case (InstructionType::SELECT): {
    SelectInstruction instruction;
    return std::make_unique<SelectInstruction>(instruction);
  }
  case (InstructionType::SELECTTYPE): {
    throw std::runtime_error("not implemented");
    // SelectInstruction instruction;
    // return std::make_unique<SelectInstruction>(instruction);
  }

  // Variable Instructions
  case (InstructionType::LOCALGET): {
    uint32_t localIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    return std::make_unique<LocalGetInstruction>(localIndex);
  }
  case (InstructionType::LOCALSET): {
    uint32_t localIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    return std::make_unique<LocalSetInstruction>(localIndex);
  }
  case (InstructionType::LOCALTEE): {
    uint32_t localIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    return std::make_unique<LocalTeeInstruction>(localIndex);
  }
  case (InstructionType::GLOBALGET): {
    uint32_t globalIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    return std::make_unique<GlobalGetInstruction>(globalIndex);
  }
  case (InstructionType::GLOBALSET): {
    uint32_t globalIndex =
        static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
    return std::make_unique<GlobalSetInstruction>(globalIndex);
  }

  // Numeric Instructions
  // 0x41
  case (InstructionType::I32CONST): {
    int32_t value =
        static_cast<int32_t>(ModuleReader::readSignedLEB128(content, pos));
    I32ConstInstruction instruction(value);
    return std::make_unique<I32ConstInstruction>(instruction);
  }

  case (InstructionType::I64CONST): {
    int64_t value =
        static_cast<int32_t>(ModuleReader::readSignedLEB128(content, pos));
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
  case InstructionType::I32EQZ:
  case InstructionType::I32EQ:
  case InstructionType::I32NE:
  case InstructionType::I32LT_S:
  case InstructionType::I32LT_U:
  case InstructionType::I32GT_S:
  case InstructionType::I32GT_U:
  case InstructionType::I32LE_S:
  case InstructionType::I32LE_U:
  case InstructionType::I32GE_S:
  case InstructionType::I32GE_U:
  case InstructionType::I64EQZ:
  case InstructionType::I64EQ:
  case InstructionType::I64NE:
  case InstructionType::I64LT_S:
  case InstructionType::I64LT_U:
  case InstructionType::I64GT_S:
  case InstructionType::I64GT_U:
  case InstructionType::I64LE_S:
  case InstructionType::I64LE_U:
  case InstructionType::I64GE_S:
  case InstructionType::I64GE_U:
  case InstructionType::F32EQ:
  case InstructionType::F32NE:
  case InstructionType::F32LT:
  case InstructionType::F32GT:
  case InstructionType::F32LE:
  case InstructionType::F32GE:
  case InstructionType::F64EQ:
  case InstructionType::F64NE:
  case InstructionType::F64LT:
  case InstructionType::F64GT:
  case InstructionType::F64LE:
  case InstructionType::F64GE: {
    return std::make_unique<ComparisonInstruction>(opcode);
  }

  case InstructionType::I32CLZ:
  case InstructionType::I32CTZ:
  case InstructionType::I32POPCNT:
  case InstructionType::I32ADD:
  case InstructionType::I32SUB:
  case InstructionType::I32MUL:
  case InstructionType::I32DIV_S:
  case InstructionType::I32DIV_U:
  case InstructionType::I32REM_S:
  case InstructionType::I32REM_U:
  case InstructionType::I32AND:
  case InstructionType::I32OR:
  case InstructionType::I32XOR:
  case InstructionType::I32SHL:
  case InstructionType::I32SHR_S:
  case InstructionType::I32SHR_U:
  case InstructionType::I32ROTL:
  case InstructionType::I32ROTR:
  case InstructionType::I64CLZ:
  case InstructionType::I64CTZ:
  case InstructionType::I64POPCNT:
  case InstructionType::I64ADD:
  case InstructionType::I64SUB:
  case InstructionType::I64MUL:
  case InstructionType::I64DIV_S:
  case InstructionType::I64DIV_U:
  case InstructionType::I64REM_S:
  case InstructionType::I64REM_U:
  case InstructionType::I64AND:
  case InstructionType::I64OR:
  case InstructionType::I64XOR:
  case InstructionType::I64SHL:
  case InstructionType::I64SHR_S:
  case InstructionType::I64SHR_U:
  case InstructionType::I64ROTL:
  case InstructionType::I64ROTR:
  case InstructionType::F32ABS:
  case InstructionType::F32NEG:
  case InstructionType::F32CEIL:
  case InstructionType::F32FLOOR:
  case InstructionType::F32TRUNC:
  case InstructionType::F32NEAREST:
  case InstructionType::F32SQRT:
  case InstructionType::F32ADD:
  case InstructionType::F32SUB:
  case InstructionType::F32MUL:
  case InstructionType::F32DIV:
  case InstructionType::F32MIN:
  case InstructionType::F32MAX:
  case InstructionType::F32COPYSIGN:
  case InstructionType::F64ABS:
  case InstructionType::F64NEG:
  case InstructionType::F64CEIL:
  case InstructionType::F64FLOOR:
  case InstructionType::F64TRUNC:
  case InstructionType::F64NEAREST:
  case InstructionType::F64SQRT:
  case InstructionType::F64ADD:
  case InstructionType::F64SUB:
  case InstructionType::F64MUL:
  case InstructionType::F64DIV:
  case InstructionType::F64MIN:
  case InstructionType::F64MAX:
  case InstructionType::F64COPYSIGN: {
    return std::make_unique<NumericOperatorInstruction>(opcode);
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
  // TODO seperate parameters and locals from compile function, because function
  // can be called multi time, but function can only be compiled once
  assert(functionIndex >= importSec.size());
  FunctionSec &function =
      functionSec.at(functionIndex - static_cast<uint32_t>(importSec.size()));
  uint32_t functionReadPos = 0;
  uint32_t localCount = static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(
      function.localsAndExpression, functionReadPos));
  for (auto &type : function.type.parameters) {
    internCallStack.back().locals.push_back({.type = type});
  }
  const uint32_t paramSize =
      static_cast<uint32_t>(function.type.parameters.size());
  if (paramSize > 0) {
    // push parameter value
    assert(internCallStack.size() > 1);
    auto &prevStack = internCallStack.at(internCallStack.size() - 2);
    for (size_t index = 0; index < paramSize; ++index) {
      auto paramValue = prevStack.functionStack.top();
      internCallStack.back().locals.at(paramSize - index - 1).value =
          paramValue.value;
      prevStack.functionStack.pop();
    }
  }

  while (localCount > 0) {
    uint32_t typeCount = static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(
        function.localsAndExpression, functionReadPos));
    uint8_t localType =
        ModuleReader::readUInt8(function.localsAndExpression, functionReadPos);
    while (typeCount > 0) {
      internCallStack.back().locals.push_back(
          {.type = static_cast<ValType>(localType)});
      typeCount--;
    }
    uint32_t localIndex = localCount--;
  }
  // TODO handle locals
  function.body =
      compileExpression(function.localsAndExpression, functionReadPos);
}

std::any Module::runFunction(uint32_t functionIndex) {
  // TODO handle parameter
  std::any result = nullptr;
  prepareFunctionCall(functionIndex);
  assert(functionIndex >= importSec.size());
  // run internal function
  FunctionSec &function = functionSec.at(functionIndex - importSec.size());
  if (function.body == nullptr) {
    compileFunction(functionIndex);
  }
  for (std::unique_ptr<Instruction> &instruction : *function.body) {
    instruction->fire(this);
  }
  cleanUpFunctionCall(functionIndex);
  return result;
}

void Module::prepareFunctionCall(uint32_t functionIndex) {
  internCallStack.push_back({functionIndex});
  runtime.setCallStack(&internCallStack.back().functionStack);
}

void Module::cleanUpFunctionCall(uint32_t functionIndex) {
  assert(internCallStack.back().functionIndex == functionIndex);
  // TODO handle return values
  assert(internCallStack.size() > 0);
  internCallStack.pop_back();
  runtime.setCallStack(&internCallStack.back().functionStack);
}
