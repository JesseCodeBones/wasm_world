#include "src/reader/ModuleReader.hpp"
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>
#include "./src/Module.hpp"

int main(int, char**){

    std::filesystem::path filePath = "/home/jesse/workspace/wasm_world/scripts/2setmemory.wasm";
    std::ifstream inputStream(filePath, std::ios::binary);
    std::vector<uint8_t> fileContents((std::istreambuf_iterator<char>(inputStream)),
                                    std::istreambuf_iterator<char>());
    Module module;
    ModuleReader moduleReader(std::move(fileContents), module);
    moduleReader.prepareSections();
    
    std::cout << "Hello, from wasm-interpreter!\n";
}
