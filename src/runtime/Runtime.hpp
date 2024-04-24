#ifndef _wasm_runtime_
#define _wasm_runtime_

#include <any>
#include <cstdint>
#include <stack>
#include <string>
#include <vector>
#include "../TypeSec.hpp"

typedef struct API {
  std::string packageName;
  std::string identifier;
  TypeSec signature;
  void *funcPtr;
  bool operator==(const API &other) {
    return packageName == other.packageName && identifier == other.identifier &&
           signature == other.signature && funcPtr == other.funcPtr;
  }
} API;

typedef union StackItemValue {
  int32_t i32;
  int64_t i64;
  float f32;
  double f64;
} StackItemValue;

typedef struct StackItem {
  ValType type;
  StackItemValue value;
} StackItem;

class Runtime {

private:
  std::vector<API> APIs;
  std::vector<uint8_t> memory;
  std::stack<StackItem> stack;

public:
  void registerAPI(std::string &&packageName, std::string &&identifier,
                   TypeSec &&signature, void *funcPtr) {
    // TODO use package name, identifer signature make a key value cache
    APIs.push_back({packageName, identifier, signature, funcPtr});
  }
  std::vector<API> &getAPIs() {
    return APIs;
  }
  void linkMemory(std::vector<uint8_t> &&_memory) {
    memory = _memory;
  }
  void *memoryBasePtr() {
    return memory.data();
  }
  std::stack<StackItem> &getStack() {
    return stack;
  }
};

#endif