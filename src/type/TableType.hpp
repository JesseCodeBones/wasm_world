#ifndef _wasm_table_type_
#define _weasm_table_type_
#include <stdint.h>
#include "LimitType.hpp"
class TableType
{
private:
    /* data */
public:
    uint8_t elementType;
    LimitType limit;
};

#endif