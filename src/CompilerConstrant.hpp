#ifndef _wasm_compiler_constrant_hpp_
#define _wasm_compiler_constrant_hpp_
#include <iostream>
namespace CONFIG {
inline bool WASM_DEBUG_OPTION;
}

#ifdef NDEBUG
// release compiler donot have trace functionality
#define WASM_DEBUG(MSG)                                                        \
  do {                                                                         \
  } while (0)
#else
#define WASM_DEBUG(MSG)                                                        \
  do {                                                                         \
    if (CONFIG::WASM_DEBUG_OPTION) {                                           \
      std::cout << "[WASM COMPILER] [TRACE]:\t" << MSG;                        \
    }                                                                          \
  } while (0)

#endif

#endif