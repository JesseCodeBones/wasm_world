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

#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include "uvwasi.h"

extern bool CONFIG::WASM_DEBUG_OPTION;

int main(int argc, char **argv) {

  uvwasi_t uvwasi;
  uvwasi_options_t init_options;
  uvwasi_errno_t err;

  /* Setup the initialization options. */
  init_options.in = 0;
  init_options.out = 1;
  init_options.err = 2;
  init_options.fd_table_size = 3;
  init_options.envp = NULL;
  init_options.preopenc = 1;
  init_options.preopens =
      (uvwasi_preopen_t *)calloc(1, sizeof(uvwasi_preopen_t));
  init_options.preopens[0].mapped_path = "/var";
  init_options.preopens[0].real_path = ".";
  init_options.allocator = NULL;
  init_options.preopen_socketc = 0;
  CONFIG::WASM_DEBUG_OPTION = false;
  std::vector<std::string> wasmArgs;
  for (int i = 0; i < argc; i++) {
    if (std::string_view(argv[i]) == "--debug") {
      CONFIG::WASM_DEBUG_OPTION = true;
    } else if (std::string_view(argv[i]).starts_with("-D")) {
      std::string_view define(argv[i]);
      define.remove_prefix(2);
      wasmArgs.emplace_back(define);
    }
  }
  init_options.argc = wasmArgs.size();
  init_options.argv = (const char **)calloc(init_options.argc, sizeof(char *));
  for (int i = 0; i < wasmArgs.size(); i++) {
    init_options.argv[i] = wasmArgs[i].c_str();
  }

  WASM_DEBUG("\b\b\b\bRunning: " << argv[argc - 1] << "\n");
  std::filesystem::path filePath = argv[argc - 1];
  std::ifstream inputStream(filePath, std::ios::binary);
  std::vector<uint8_t> fileContents(
      (std::istreambuf_iterator<char>(inputStream)),
      std::istreambuf_iterator<char>());
  Module module;
  SampleRuntime::registerRuntime(module);
  ModuleReader moduleReader(std::move(fileContents), module);
  moduleReader.prepareModule();
  /* Initialize the sandbox. */
  err = uvwasi_init(&uvwasi, &init_options);
  module.uvwasi = &uvwasi;
  module.execute();
  uvwasi_destroy(&uvwasi);
}
