#ifndef _wasm_runtime_
#define _wasm_runtime_

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

class Runtime {

private:
  std::vector<API> APIs;

public:
  void registerAPI(std::string &&packageName, std::string &&identifier,
                   TypeSec &&signature, void *funcPtr) {
    // TODO use package name, identifer signature make a key value cache
    APIs.push_back({packageName, identifier, signature, funcPtr});
  }
  std::vector<API> &getAPIs() {
    return APIs;
  }
};

#endif