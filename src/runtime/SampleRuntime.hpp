#ifndef _wasm_sample_runtime_
#define _wasm_sample_runtime_

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include "../Module.hpp"
#include "Runtime.hpp"

class SampleRuntime {

private:
  static void println(Module *module) {
    uint8_t *ptr = (uint8_t *)module->runtime.memoryBasePtr();
    uint32_t offset = module->runtime.getStack()->top().value.i32;
    module->runtime.getStack()->pop();
    ptr += offset;
    std::cout << (char *)ptr << std::endl;
  }

  static void printNumber(Module *module) {
    StackItem number = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    switch (number.type) {
    case ValType::i32: {
      std::cout << std::to_string(number.value.i32) << std::endl;
      break;
    }
    case ValType::i64: {
      std::cout << std::to_string(number.value.i64) << std::endl;
      break;
    }
    case ValType::f32: {
      std::cout << std::fixed << std::setprecision(5) << number.value.f32
                << std::endl;
      break;
    }
    case ValType::f64: {
      std::cout << std::fixed << std::setprecision(5) << number.value.f64
                << std::endl;
      break;
    }
    default: {
      throw std::runtime_error("unsupported stack type");
    }
    }
  }

  static void abort(Module *module) {
    StackItem i321 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i322 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i323 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i324 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    std::cout << "abort called with code: " << i321.value.i32 << " at "
              << i322.value.i32 << ":" << i323.value.i32
              << " stack size: " << i324.value.i32 << std::endl;
    std::abort();
  }

  static void trace(Module *module) {
    StackItem i321 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i322 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem f641 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem f642 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem f643 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem f644 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem f645 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    std::cout << "abort called with code: " << i321.value.i32 << " at "
              << i322.value.i32 << std::endl;
    std::abort();
  }

public:
  static void registerRuntime(Module &module) {
    TypeSec vi32;
    vi32.parameters.emplace_back(ValType::i32);
    TypeSec vi64;
    vi64.parameters.emplace_back(ValType::i64);
    TypeSec vf32;
    vf32.parameters.emplace_back(ValType::f32);
    TypeSec vf64;
    vf64.parameters.emplace_back(ValType::f64);
    TypeSec VI32I32I32I32;
    VI32I32I32I32.parameters.emplace_back(ValType::i32);
    VI32I32I32I32.parameters.emplace_back(ValType::i32);
    VI32I32I32I32.parameters.emplace_back(ValType::i32);
    VI32I32I32I32.parameters.emplace_back(ValType::i32);

    TypeSec VI32I32F32F32F32F32F32;
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::i32);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::i32);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::f64);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::f64);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::f64);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::f64);
    VI32I32F32F32F32F32F32.parameters.emplace_back(ValType::f64);

    module.runtime.registerAPI("env", "println", std::move(vi32),
                               (void *)&SampleRuntime::println);
    module.runtime.registerAPI("env", "printNumber", std::move(vi32),
                               (void *)&SampleRuntime::printNumber);
    module.runtime.registerAPI("env", "printNumber", std::move(vi64),
                               (void *)&SampleRuntime::printNumber);
    module.runtime.registerAPI("env", "printNumber", std::move(vf32),
                               (void *)&SampleRuntime::printNumber);
    module.runtime.registerAPI("env", "printNumber", std::move(vf64),
                               (void *)&SampleRuntime::printNumber);
    module.runtime.registerAPI("env", "abort", std::move(VI32I32I32I32),
                               (void *)&SampleRuntime::abort);
    module.runtime.registerAPI("env", "trace",
                               std::move(VI32I32F32F32F32F32F32),
                               (void *)&SampleRuntime::trace);
  }
};

#endif