#ifndef _wasm_ref_type_
#define _wasm_ref_type_

#include <cstdint>
enum class RefType : uint8_t { FuncRef = 0x70, ExternRef = 0x6F };

#endif