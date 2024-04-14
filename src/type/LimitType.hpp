#ifndef _wasm_limit_type_
#define _wasm_limit_type_
#include <stdint.h>
class LimitType
{
private:
    /* data */
public:
    LimitType(/* args */);
    ~LimitType();

    uint8_t tag;
    uint32_t min;
    uint32_t max;
};

#endif