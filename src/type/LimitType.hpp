#ifndef _wasm_limit_type_
#define _wasm_limit_type_
#include <cstdint>
#include <stdint.h>
#include <limits.h>
class LimitType
{
private:
    /* data */
public:
    uint8_t tag = 0;
    uint32_t min = UINT32_MAX;
    uint32_t max = UINT32_MAX;
};

#endif