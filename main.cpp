#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include "./src/Module.hpp"
#include "src/reader/ModuleReader.hpp"
#include "src/runtime/SampleRuntime.hpp"

int main(int, char **) {

  std::filesystem::path filePath =
      "/home/jesse/workspace/wasm_world/scripts/7global.wasm";
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
