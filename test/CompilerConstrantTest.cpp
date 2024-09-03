#include "CompilerConstrant.hpp"
#include <gtest/gtest.h>
#define ALIGN_UP(x, align) (((x) + (align - 1)) & ~(align - 1))
TEST(StorageTank, empty_with_temperature) {
  std::cout << ALIGN_UP(161 + 0, 0);
}