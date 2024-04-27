cmake_minimum_required(VERSION 3.0.0)
project(wasm-interpreter VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

aux_source_directory(src sources)
aux_source_directory(src/reader sources)

add_executable(wasm-interpreter main.cpp ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
