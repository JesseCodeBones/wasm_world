#ifndef _wasm_call_instruction_
#define _wasm_call_instruction_
#include <algorithm>
#include <cstdint>
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
      uint32_t internFunctionIndex = functionIndex - module->importSec.size();
      FunctionSec &function = module->functionSec.at(internFunctionIndex);
      module->runFunction(functionIndex);
    }
  }

private:
  uint32_t functionIndex;
};
#endif