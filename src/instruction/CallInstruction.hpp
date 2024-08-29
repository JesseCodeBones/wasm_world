#ifndef _wasm_call_instruction_
#define _wasm_call_instruction_
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include "../CompilerConstrant.hpp"
#include "../Module.hpp"
#include "Instruction.hpp"

typedef void (*externalFuncType)(void *a);

class CallInstruction : public Instruction {
public:
  CallInstruction(int32_t functionIndex) : functionIndex(functionIndex) {
    type = InstructionType::CALL;
  }

  void fire(void *modulePtr) {
    Module *module = (Module *)modulePtr;
    if (functionIndex < module->importSec.size()) {
      // call external
      WASM_DEBUG("call external function: " << functionIndex << "\n");
      auto &externalFunc = module->importSec.at(functionIndex);
      // TODO optimize target function search logic
      auto foundFun = std::find_if(
          module->runtime.getAPIs().cbegin(), module->runtime.getAPIs().cend(),
          [&](const API &api) {
            return externalFunc.getPackage() == api.packageName &&
                   externalFunc.getIdentifier() == api.identifier &&
                   module->typeSec.at(externalFunc.getFunctionTypeIndex()) ==
                       api.signature;
          });
      const API &foundAPI = *foundFun;
      externalFuncType actual = (externalFuncType)foundAPI.funcPtr;
      actual(module);
    } else {
      // call internal
      uint32_t internFunctionIndex =
          functionIndex - static_cast<uint32_t>(module->importSec.size());
      WASM_DEBUG("call internal function: " << functionIndex << "\n");
      FunctionSec &function = module->functionSec.at(internFunctionIndex);
      module->runFunction(functionIndex);
    }
  }

private:
  uint32_t functionIndex;
};

class CallIndirectInstruction : public Instruction {
public:
  CallIndirectInstruction(uint32_t tableIndex, uint32_t typeIndex)
      : tableIndex(tableIndex), typeIndex(typeIndex) {
    type = InstructionType::CALL_INDIRECT;
  }
  void fire(void *modulePtr) override {
    Module *ptr = (Module *)modulePtr;
    StackItem tableIndexStackItem = ptr->runtime.getStack()->top();
    ptr->runtime.getStack()->pop();
    uint32_t tableIndex = tableIndexStackItem.value.i32;
    if (tableIndex >= ptr->runtime.getTable().size()) {
      throw std::runtime_error("table index out of range");
    }
    auto &tableValue = ptr->runtime.getTable()[tableIndex];
    if (tableValue == static_cast<uint32_t>(-1)) {
      throw std::runtime_error("undefined table element");
    }
    if (tableValue >= ptr->importSec.size() &&
        !(ptr->functionSec[tableValue - ptr->importSec.size()].type ==
          ptr->typeSec[typeIndex])) {
      throw std::runtime_error("indirect call type mismatch");
    }
    WASM_DEBUG("call indirect function: " << tableValue << ", table index: "
                                          << tableIndex << "\n");
    ptr->runFunction(tableValue);
  }

private:
  uint32_t tableIndex;
  uint32_t typeIndex;
};

#endif