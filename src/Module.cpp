#include "./Module.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "type/ImportDType.hpp"
void Module::dumpInfo() {
  std::cout << "------------------Module Info------------------" << std::endl;
}

void Module::checkImport() {
  for (auto &importItem : importSec) {
    switch (importItem.getType()) {
    case ImportDType::FUNC: {
      uint32_t functionIndex = importItem.getFunctionTypeIndex();
      assert(typeSec.size() > functionIndex);
      // TODO link runtime to import section
      break;
    }
    default: {
      throw std::runtime_error("not implemented");
    }
    }
  }
}
