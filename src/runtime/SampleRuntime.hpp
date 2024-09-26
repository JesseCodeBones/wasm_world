#ifndef _wasm_sample_runtime_
#define _wasm_sample_runtime_

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>
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

  static void readFileContent(Module *module) {
    StackItem i323 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i322 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    StackItem i321 = module->runtime.getStack()->top();
    module->runtime.getStack()->pop();
    int32_t fileNameWasmMemoryOffset = i321.value.i32;
    char *fileName = (char *)module->runtime.memoryPtr(i321.value.i32);
    fileName += fileNameWasmMemoryOffset;
    std::ifstream input(fileName);
    if (!input) {
      throw std::runtime_error("cannot open file\n");
    }
    input.seekg(0, std::ios::end);
    uint32_t size{static_cast<uint32_t>(input.tellg()) + 1U};
    input.seekg(0, std::ios::beg);
    // std::unique_ptr<char[]> content(new char[size]{});
    char *contentPtr = (char *)module->runtime.memoryPtr(i323.value.i32);
    input.read(contentPtr, size);
    input.close();
    uint32_t *sizePtr = (uint32_t *)module->runtime.memoryPtr(i322.value.i32);
    *sizePtr = size;
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
    std::cout << "abort called with code: " << std::dec << i321.value.i32
              << " at " << i322.value.i32 << ":" << i323.value.i32
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
    std::cout << "trace called with code: " << i321.value.i32 << " at "
              << i322.value.i32 << std::endl;
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

    TypeSec VI32I32I32;
    VI32I32I32.parameters.emplace_back(
        ValType::i32); // param 1: file name from wasm memory
    VI32I32I32.parameters.emplace_back(
        ValType::i32); // param 2: size of file content to be written to wasm
                       // memory
    VI32I32I32.parameters.emplace_back(
        ValType::i32); // param 3: offset in wasm memory to write file content

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
    module.runtime.registerAPI("env", "readFileContent", std::move(VI32I32I32),
                               (void *)&SampleRuntime::readFileContent);
  }
};

#endif