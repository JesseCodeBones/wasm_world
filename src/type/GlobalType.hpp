#ifndef _wasm_globel_type_
#define _wasm_global_type_

#define WASM_TYPE_IMMUTABLE 0
#define WASM_TYPE_MUTABLE 1

#include <stdint.h>
#include "ValType.hpp"

class GlobalType
{
private:
    /* data */
public:
    ValType type;
    uint8_t mut;
};

#endif