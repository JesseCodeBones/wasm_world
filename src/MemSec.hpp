#ifndef _wasm_memory_sec_
#define _wasm_memory_sec_
#include "AbstractSec.hpp"
#include "./type/LimitType.hpp"
class MemSec : public AbstractSec
{
private:
 LimitType limit;
public:
};


#endif