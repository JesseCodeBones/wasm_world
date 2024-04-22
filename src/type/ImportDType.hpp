#ifndef _wasm_import_d_type_
#define _wasm_import_d_type_
#include <stdint.h>
enum class ImportDType : uint8_t {
  FUNC = 0U,
  TABLE = 1U,
  MEM = 2U,
  GLOBAL = 3U
};

#endif
