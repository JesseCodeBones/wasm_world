#ifndef _wasm_function_type_
#define _wasm_function_type_
#include "ValType.hpp"
#include <vector>
class FunctionType
{
private:
    /* data */
public:
    std::vector<ValType> paramsType;
    std::vector<ValType> resultsType;

};

#endif