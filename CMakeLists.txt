cmake_minimum_required(VERSION 2.6)

project(SERINE CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g")

file(GLOB_RECURSE SERINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src" "*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(serine STATIC ${SERINE_SOURCES})

enable_testing()

add_executable(MemoryArchiverTest tests/MemoryArchiverTest.cpp)
target_link_libraries(MemoryArchiverTest serine)
add_test(MemoryArchiverTest MemoryArchiverTest)