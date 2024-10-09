cmake_minimum_required(VERSION 3.0.0)
project(wasm-interpreter VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

if (WIN32)
    add_definitions(-DNOMINMAX)
endif()

aux_source_directory(src sources)
aux_source_directory(src/reader sources)
aux_source_directory(src/instruction sources)

if("${CMAKE_BUILD_TYPE}" MATCHES "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -rdynamic")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -rdynamic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
    message("Release mode")
endif()

add_executable(wasm-interpreter main.cpp ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(BUILD_WITH_UNIT_TEST)
    add_subdirectory(test)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(thirdparty/uvwasi)
target_link_libraries(wasm-interpreter PRIVATE uvwasi_a)

target_include_directories(wasm-interpreter PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty/uvwasi/include)
target_include_directories(wasm-interpreter PRIVATE ${PROJECT_SOURCE_DIR}/build/_deps/libuv-src/include)
