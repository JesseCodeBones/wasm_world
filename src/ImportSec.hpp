#ifndef _wasm_import_sec_
#define _wasm_import_sec_

#include <cstdint>
#include <string>
#include <string_view>
#include "./type/ImportDType.hpp"
#include "AbstractSec.hpp"
class ImportSec : public AbstractSec {
private:
  std::string package;
  std::string identifier;
  ImportDType type;
  uint32_t functionTypeIndex;

public:
  ImportSec(std::string &&package, std::string &&identifier, ImportDType desc)
      : package(package), identifier(identifier), type(desc) {
  }
  void setFunctionIndex(uint32_t index) {
    functionTypeIndex = index;
  }
  ImportDType getType() {
    return type;
  }
  uint32_t getFunctionTypeIndex() {
    return functionTypeIndex;
  }
  std::string_view getPackage() {
    return package;
  }
  std::string_view getIdentifier() {
    return identifier;
  }
};
#endif
