#ifndef _wasm_table_type_
#define _weasm_table_type_
#include <stdint.h>
#include "LimitType.hpp"
class TableType
{
private:
    /* data */
public:
    TableType(/* args */);
    ~TableType();
    uint8_t elementType;
    LimitType limit;
};

TableType::TableType(/* args */)
{
}

TableType::~TableType()
{
}

#endif