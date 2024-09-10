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
#include "CompilerConstrant.hpp"
#include "FunctionSec.hpp"
#include "ImportSec.hpp"
#include "TypeSec.hpp"
#include "instruction/CallInstruction.hpp"
#include "instruction/ControlInstruction.hpp"
#include "instruction/Instruction.hpp"
#include "instruction/MemoryInstruction.hpp"
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
      if (ifFound == runtime.getAPIs().end()) {
        throw std::runtime_error(
            "import function not found in current runtime");
      }
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
    if (static_cast<uint32_t>(-1) == _startFunctionIndex) {
      throw std::runtime_error("Module does not have start function");
    } else {
      runFunction(_startFunctionIndex);
    }
  } else {
    runFunction(startIndex);
  }
}

std::unique_ptr<Instruction>
Module::compileInstruction(InstructionType opcode,
                           std::vector<uint8_t> &content, uint32_t &pos) {
  WASM_DEBUG("[compile] compile opcode: "
             << opcodePrinter.getOPCodeName(static_cast<uint8_t>(opcode))
             << std::endl);
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
    return std::make_unique<I32ConstInstruction>(value);
  }

  case (InstructionType::I64CONST): {
    int64_t value =
        static_cast<int64_t>(ModuleReader::readSignedLEB128(content, pos));
    return std::make_unique<I64ConstInstruction>(value);
  }

  case (InstructionType::F32CONST): {
    float value = ModuleReader::bit_cast<float>(
        ModuleReader::read4BytesLittleEndian(content, pos));
    return std::make_unique<F32ConstInstruction>(value);
  }

  case (InstructionType::F64CONST): {
    double value = ModuleReader::bit_cast<double>(
        ModuleReader::read8BytesLittleEndian(content, pos));
    return std::make_unique<F64ConstInstruction>(value);
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
  case InstructionType::F64COPYSIGN:

  case InstructionType::I32WRAP_I64:
  case InstructionType::I32TRUNC_S_F32:
  case InstructionType::I32TRUNC_U_F32:
  case InstructionType::I32TRUNC_S_F64:
  case InstructionType::I32TRUNC_U_F64:
  case InstructionType::I64EXTEND_S_I32:
  case InstructionType::I64EXTEND_U_I32:
  case InstructionType::I64TRUNC_S_F32:
  case InstructionType::I64TRUNC_U_F32:
  case InstructionType::I64TRUNC_S_F64:
  case InstructionType::I64TRUNC_U_F64:
  case InstructionType::F32CONVERT_S_I32:
  case InstructionType::F32CONVERT_U_I32:
  case InstructionType::F32CONVERT_S_I64:
  case InstructionType::F32CONVERT_U_I64:
  case InstructionType::F32DEMOTE_F64:
  case InstructionType::F64CONVERT_S_I32:
  case InstructionType::F64CONVERT_U_I32:
  case InstructionType::F64CONVERT_S_I64:
  case InstructionType::F64CONVERT_U_I64:
  case InstructionType::F64PROMOTE_F32:
  case InstructionType::I32REINTERPRET_F32:
  case InstructionType::I64REINTERPRET_F64:
  case InstructionType::F32REINTERPRET_I32:
  case InstructionType::F64REINTERPRET_I64:
  case InstructionType::I32EXTEND8_S:
  case InstructionType::I32EXTEND16_S:
  case InstructionType::I64EXTEND8_S:
  case InstructionType::I64EXTEND16_S:
  case InstructionType::I64EXTEND32_S:

  {
    return std::make_unique<NumericOperatorInstruction>(opcode);
  }

  case InstructionType::UNREACHABLE:
  case InstructionType::NOP:
  case InstructionType::BLOCK:
  case InstructionType::LOOP:
  case InstructionType::IF:
  case InstructionType::ELSE:
  case InstructionType::TRY:
  case InstructionType::CATCH:
  case InstructionType::THROW:
  case InstructionType::RETHROW:
  case InstructionType::UNUSED_0x0a:
  case InstructionType::END:
  case InstructionType::BR:
  case InstructionType::BR_IF:
  case InstructionType::BR_TABLE:
  case InstructionType::RETURN:
  case InstructionType::CALL_INDIRECT:
  case InstructionType::RETURN_CALL:
  case InstructionType::RETURN_CALL_INDIRECT:
  case InstructionType::CALL_REF:
  case InstructionType::RETURN_CALL_REF: {
    switch (opcode) {
    case InstructionType::IF: {
      std::unique_ptr<IfInstruction> ifInstruction =
          std::make_unique<IfInstruction>(opcode);
      uint8_t valType = ModuleReader::readUInt8(content, pos);
      ifInstruction->setHasReturn(valType != 0x40);
      if (ifInstruction->getHasReturn()) {
        ifInstruction->setBlockType(static_cast<ValType>(valType));
      }
      // then block
      InstructionType opCode =
          static_cast<InstructionType>(ModuleReader::readUInt8(content, pos));
      while (opCode != InstructionType::END &&
             opCode != InstructionType::ELSE) {
        auto instruction = compileInstruction(opCode, content, pos);
        ifInstruction->thenInstructions->push_back(std::move(instruction));
        opCode =
            static_cast<InstructionType>(ModuleReader::readUInt8(content, pos));
      }
      if (opCode == InstructionType::ELSE) {
        opCode =
            static_cast<InstructionType>(ModuleReader::readUInt8(content, pos));
        while (opCode != InstructionType::END) {
          auto instruction = compileInstruction(opCode, content, pos);
          ifInstruction->elseInstructions->push_back(std::move(instruction));
          opCode = static_cast<InstructionType>(
              ModuleReader::readUInt8(content, pos));
        }
      }

      return std::move(ifInstruction);
      break;
    }
    // ELSE instruction will not be handled by compile instruction function but
    // in compile IF instruction
    case InstructionType::ELSE: {
      throw std::runtime_error(
          "ELSE instruction will not be handled by compile instruction "
          "function but in compile IF instruction");
    }
    case InstructionType::LOOP: {
      auto type = ModuleReader::readUInt8(content, pos);
      auto loopInstruction = std::make_unique<LoopInstruction>(opcode);
      loopInstruction->instructions = compileExpression(content, pos);
      return std::move(loopInstruction);
    }
    case InstructionType::BR: {
      uint32_t targetIndex =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      return std::make_unique<BRInstruction>(opcode, targetIndex);
    }
    case InstructionType::BR_IF: {
      uint32_t targetIndex =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      return std::make_unique<BRIFInstruction>(opcode, targetIndex);
    }

    case InstructionType::BLOCK: {
      auto type = ModuleReader::readUInt8(content, pos);
      auto blockInstruction = std::make_unique<BlockInstruction>();
      blockInstruction->instructions = compileExpression(content, pos);
      return blockInstruction;
    }

    case InstructionType::CALL_INDIRECT: {
      uint32_t typeIndex =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      uint32_t tableIndex =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      return std::make_unique<CallIndirectInstruction>(tableIndex, typeIndex);
    }

    case InstructionType::BR_TABLE: {
      uint32_t indexesCount =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      std::vector<uint32_t> targetIndexes;
      while (indexesCount > 0) {
        uint32_t targetIndex = static_cast<uint32_t>(
            ModuleReader::readUnsignedLEB128(content, pos));
        targetIndexes.push_back(targetIndex);
        indexesCount--;
      }
      uint32_t defaultIndex =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      return std::make_unique<BRTableInstruction>(
          opcode, std::move(targetIndexes), defaultIndex);
    }

    default: break;
    }
    return std::make_unique<ControlInstruction>(opcode);
  }
  case InstructionType::I32_LOAD:
  case InstructionType::I64_LOAD:
  case InstructionType::F32_LOAD:
  case InstructionType::F64_LOAD:
  case InstructionType::I32_LOAD8_S:
  case InstructionType::I32_LOAD8_U:
  case InstructionType::I32_LOAD16_S:
  case InstructionType::I32_LOAD16_U:
  case InstructionType::I64_LOAD8_S:
  case InstructionType::I64_LOAD8_U:
  case InstructionType::I64_LOAD16_S:
  case InstructionType::I64_LOAD16_U:
  case InstructionType::I64_LOAD32_S:
  case InstructionType::I64_LOAD32_U:
  case InstructionType::I32_STORE:
  case InstructionType::I64_STORE:
  case InstructionType::F32_STORE:
  case InstructionType::F64_STORE:
  case InstructionType::I32_STORE8:
  case InstructionType::I32_STORE16:
  case InstructionType::I64_STORE8:
  case InstructionType::I64_STORE16:
  case InstructionType::I64_STORE32:
  case InstructionType::MEMORY_SIZE:
  case InstructionType::MEMORY_GROW: {
    auto memoryInstruction = std::make_unique<MemoryInstruction>(opcode);
    switch (opcode) {
    case InstructionType::I32_STORE:
    case InstructionType::I32_LOAD:
    case InstructionType::I64_STORE:
    case InstructionType::I64_LOAD:
    case InstructionType::F32_STORE:
    case InstructionType::F32_LOAD:
    case InstructionType::F64_STORE:
    case InstructionType::F64_LOAD:
    case InstructionType::I32_LOAD8_S:
    case InstructionType::I32_LOAD8_U:
    case InstructionType::I32_LOAD16_S:
    case InstructionType::I32_LOAD16_U:
    case InstructionType::I64_LOAD8_S:
    case InstructionType::I64_LOAD8_U:
    case InstructionType::I64_LOAD16_S:
    case InstructionType::I64_LOAD16_U:
    case InstructionType::I64_LOAD32_S:
    case InstructionType::I64_LOAD32_U:
    case InstructionType::I32_STORE8:
    case InstructionType::I32_STORE16:
    case InstructionType::I64_STORE8:
    case InstructionType::I64_STORE16:
    case InstructionType::I64_STORE32: {
      uint32_t align =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      uint32_t offset =
          static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(content, pos));
      memoryInstruction->memoryAlign = align;
      memoryInstruction->memoryOffset = offset;
      break;
    }
    case InstructionType::MEMORY_SIZE:
    case InstructionType::MEMORY_GROW: {
      ModuleReader::readUInt8(content, pos);
      break;
    }
    default: {
      break;
    }
    }
    return memoryInstruction;
  }

  case InstructionType::TWO_BYTE_INS_FLAG: {
    uint32_t secondIndex =

        ModuleReader::readUnsignedLEB128(content, pos);

    switch (secondIndex) {

    case TruncSatNumberInstructionOpcode::I32_TRUNC_SAT_F32_S:
    case TruncSatNumberInstructionOpcode::I32_TRUNC_SAT_F32_U:
    case TruncSatNumberInstructionOpcode::I32_TRUNC_SAT_F64_S:
    case TruncSatNumberInstructionOpcode::I32_TRUNC_SAT_F64_U:
    case TruncSatNumberInstructionOpcode::I64_TRUNC_SAT_F32_S:
    case TruncSatNumberInstructionOpcode::I64_TRUNC_SAT_F32_U:
    case TruncSatNumberInstructionOpcode::I64_TRUNC_SAT_F64_S:
    case TruncSatNumberInstructionOpcode::I64_TRUNC_SAT_F64_U: {
      auto truncSatIns = std::make_unique<TruncSatNumberInstruction>(
          static_cast<TruncSatNumberInstructionOpcode>(secondIndex));
      return truncSatIns;
    }

    case 11: { // memory fill
      auto bulkIns = std::make_unique<BulkMemoryInstruction>(opcode);
      bulkIns->secondIndex =
          static_cast<BulkSecondInstructionType>(secondIndex);
      uint8_t flag = ModuleReader::readUInt8(content, pos);
      assert(flag == 0x00);
      bulkIns->u8_1 = 0x00;
      return bulkIns;
    }
    case 10: { // memory copy
      auto bulkIns = std::make_unique<BulkMemoryInstruction>(opcode);
      bulkIns->secondIndex =
          static_cast<BulkSecondInstructionType>(secondIndex);
      uint8_t flag1 = ModuleReader::readUInt8(content, pos);
      uint8_t flag2 = ModuleReader::readUInt8(content, pos);
      assert(flag1 == 0x00);
      assert(flag2 == 0x00);
      bulkIns->u8_1 = 0x00;
      bulkIns->u8_2 = 0x00;
      return bulkIns;
    }
    default: {
      throw std::runtime_error("not implemented");
    }
    }
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
    auto instruction = compileInstruction(opCode, content, pos);
    result->push_back(std::move(instruction));
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
    function.locals.push_back({.type = type});
  }
  const uint32_t paramSize =
      static_cast<uint32_t>(function.type.parameters.size());
  function.paramSize = paramSize;
  // if (paramSize > 0) {
  //   // push parameter value
  //   assert(internCallStack.size() > 1);
  //   auto &prevStack = internCallStack.at(internCallStack.size() - 2);
  //   for (size_t index = 0; index < paramSize; ++index) {
  //     auto paramValue = prevStack.functionStack.top();
  //     internCallStack.back().locals.at(paramSize - index - 1).value =
  //         paramValue.value;
  //     prevStack.functionStack.pop();
  //   }
  // }

  while (localCount > 0) {
    uint32_t typeCount = static_cast<uint32_t>(ModuleReader::readUnsignedLEB128(
        function.localsAndExpression, functionReadPos));
    uint8_t localType =
        ModuleReader::readUInt8(function.localsAndExpression, functionReadPos);
    while (typeCount > 0) {
      ValItem localItem = {.type = static_cast<ValType>(localType)};
      switch (localItem.type) {
      case ValType::i64: {
        localItem.value = StackItemValue{.i64 = 0};
        break;
      }
      case ValType::f32: {
        localItem.value = StackItemValue{.f32 = 0.0f};
        break;
      }
      case ValType::f64: {
        localItem.value = StackItemValue{.f64 = 0.0};
        break;
      }
      default: {
        localItem.value = StackItemValue{.i32 = 0};
        // other type make as i32 type
        break;
      }
      }
      function.locals.push_back(std::move(localItem));
      typeCount--;
    }
    uint32_t localIndex = localCount--;
  }
  // TODO handle locals
  function.body =
      compileExpression(function.localsAndExpression, functionReadPos);
}

std::any Module::runFunction(uint32_t functionIndex) {
  WASM_DEBUG("\b\b\b\brun function: " << functionIndex << "\n");
  std::any result = nullptr;
  prepareFunctionCall(functionIndex);
  assert(functionIndex >= importSec.size());
  // run internal function
  FunctionSec &function = functionSec.at(functionIndex - importSec.size());
  if (function.body == nullptr) {
    compileFunction(functionIndex);
  }

  // push local slots
  for (auto local : function.locals) {
    internCallStack.back().locals.push_back(local);
  }

  // push parameter to locals
  uint32_t paramSize = function.paramSize;
  if (paramSize > 0) {
    assert(internCallStack.size() > 1);
    auto &prevStack = internCallStack.at(internCallStack.size() - 2);
    for (size_t index = 0; index < paramSize; ++index) {
      auto paramValue = prevStack.functionStack.top();
      internCallStack.back().locals.at(paramSize - index - 1).value =
          paramValue.value;
      prevStack.functionStack.pop();
    }
  }

  // read execute zone
  auto &bodyInstructions = *function.body;
  for (std::unique_ptr<Instruction> &instruction : bodyInstructions) {
    instruction->fire(this);
    if (internCallStack.back().returnFlag) {
      break;
    }
  }
  WASM_DEBUG("\b\b\b\brun function end: " << functionIndex << "\n");
  cleanUpFunctionCall(functionIndex);
  return result;
}

void Module::prepareFunctionCall(uint32_t functionIndex) {
  internCallStack.push_back(
      {.functionIndex = functionIndex, .returnFlag = false});
  runtime.setCallStack(&internCallStack.back().functionStack);
}

void Module::cleanUpFunctionCall(uint32_t functionIndex) {
  assert(internCallStack.back().functionIndex == functionIndex);
  FunctionSec &function = functionSec.at(functionIndex - importSec.size());
  if (!function.type.returns.empty()) {
    StackItem returnStackItem = internCallStack.back().functionStack.top();
    if (internCallStack.size() > 1) {
      internCallStack.at(internCallStack.size() - 2)
          .functionStack.push(returnStackItem);
    }
  }
  assert(internCallStack.size() > 0);
  internCallStack.pop_back();
  runtime.setCallStack(&internCallStack.back().functionStack);
}
