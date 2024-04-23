#ifndef _wasm_sample_runtime_
#define _wasm_sample_runtime_

#include <any>
#include <cstdint>
#include <iostream>
#include "../Module.hpp"
#include "Runtime.hpp"

class SampleRuntime {

private:
  static void println(Module *module) {
    uint8_t *ptr = (uint8_t *)module->runtime.memoryBasePtr();
    uint32_t offset = std::any_cast<int32_t>(module->runtime.getStack().top());
    module->runtime.getStack().pop();
    ptr += offset;
    std::cout << (char *)ptr << std::endl;
  }

public:
  static void registerRuntime(Module &module) {
    TypeSec sec;
    sec.parameters.emplace_back(ValType::i32);
    module.runtime.registerAPI("env", "println", std::move(sec),
                               (void *)&SampleRuntime::println);
  }
};

#endif