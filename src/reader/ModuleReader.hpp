#ifndef _wasm_module_reader_
#define _wasm_module_reader_
#include "ModuleSection.hpp"
#include <cstdint>
#include <stdint.h>
#include <vector>
#include "../Module.hpp"
class ModuleReader{
public:
ModuleReader(std::vector<uint8_t> &&src, Module& _module):data(src), module(_module){
}

void prepareSections();

private:
    std::vector<uint8_t> data;
    Module& module;
    uint32_t pos = 0U;
    ModuleSection memorySection;
    ModuleSection dataSection;

    uint32_t readUInt32();
    uint8_t readUInt8(std::vector<uint8_t> &binary, uint32_t &ptr);
    void readSection(uint32_t &secSize, std::vector<uint8_t>& secData);
    uint64_t readUnsignedLEB128(std::vector<uint8_t> &binary, uint32_t &ptr);
    int64_t readSignedLEB128();
    void handleMemorySection();
};
#endif