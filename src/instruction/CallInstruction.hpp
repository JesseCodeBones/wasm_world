#ifndef _wasm_call_instruction_
#define _wasm_call_instruction_
#include <algorithm>
#include <cstdint>
#include <tuple>
#include <utility>
#include "Instruction.hpp"

typedef void (*externalFuncType)(Module *a);

class CallInstruction : public Instruction {
public:
  CallInstruction(int32_t functionIndex) : functionIndex(functionIndex) {
    type = InstructionType::CALL;
  }

  void fire(Module *module) {
    if (functionIndex < module->importSec.size()) {
      // call external
      auto &externalFunc = module->importSec.at(functionIndex);
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
    }
  }

private:
  uint32_t functionIndex;
};
#endif