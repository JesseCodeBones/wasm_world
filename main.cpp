#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string_view>
#include "./src/Module.hpp"
#include "src/CompilerConstrant.hpp"
#include "src/reader/ModuleReader.hpp"
#include "src/runtime/SampleRuntime.hpp"

extern bool CONFIG::WASM_DEBUG_OPTION;

int main(int argc, char **argv) {

  // std::filesystem::path filePath =
  //     "/home/jesse/workspace/wasm_world/scripts/7global.wasm";
  CONFIG::WASM_DEBUG_OPTION = false;
  // loop args
  for (int i = 0; i < argc; i++) {
    if (std::string_view(argv[i]) == "--debug") {
      CONFIG::WASM_DEBUG_OPTION = true;
    }
  }

  WASM_DEBUG("Running: " << argv[argc - 1] << "\n");
  std::filesystem::path filePath = argv[argc - 1];
  std::ifstream inputStream(filePath, std::ios::binary);
  std::vector<uint8_t> fileContents(
      (std::istreambuf_iterator<char>(inputStream)),
      std::istreambuf_iterator<char>());
  Module module;
  SampleRuntime::registerRuntime(module);
  ModuleReader moduleReader(std::move(fileContents), module);
  moduleReader.prepareModule();
  module.execute();
}
