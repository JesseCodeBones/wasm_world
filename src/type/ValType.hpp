#ifndef _wasm_type_
#define _wasm_type_
#include <stdint.h>
class ValType
{
private:
    /* data */
public:

    const static uint8_t i32 = 0x7f;
    const static uint8_t i64 = 0x7e;
    const static uint8_t f32 = 0x7d;
    const static uint8_t f64 = 0x7c;
};
#endif