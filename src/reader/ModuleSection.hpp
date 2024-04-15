#ifndef _wasm_module_section
#define _wasm_module_section

#include <cstdint>
#include <vector>
typedef struct {
    uint32_t size;
    std::vector<uint8_t> content;
} ModuleSection;

#endif