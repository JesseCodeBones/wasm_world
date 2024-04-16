#ifndef _wasm_limit_type_
#define _wasm_limit_type_
#include <stdint.h>
class LimitType
{
private:
    /* data */
public:
    uint8_t tag = 0;
    uint32_t min = 0;
    uint32_t max = 0;
};

#endif