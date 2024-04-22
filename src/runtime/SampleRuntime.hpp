#ifndef _wasm_sample_runtime_
#define _wasm_sample_runtime_

#include <iostream>
#include "../Module.hpp"

class SampleRuntime {

private:
  static void println(char *str) {
    std::cout << str << std::endl;
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