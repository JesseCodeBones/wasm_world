find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ./*.cpp)
aux_source_directory(../src test_sources)
aux_source_directory(../src/reader test_sources)
aux_source_directory(../src/instruction test_sources)

include_directories(
  ${GTEST_INCLUDE_DIRS}
  ../src
  ../src/reader
  ../src/instruction
)

add_executable(
  wasm_world_test
  ${test_sources}
)

target_link_libraries(
  wasm_world_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(wasm_world_test)
