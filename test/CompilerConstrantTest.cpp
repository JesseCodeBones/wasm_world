#include "CompilerConstrant.hpp"
#include <gtest/gtest.h>
TEST(StorageTank, empty_with_temperature) {
  CONFIG::WASM_DEBUG_OPTION = true;
  WASM_DEBUG("Hello, World!\n");
}