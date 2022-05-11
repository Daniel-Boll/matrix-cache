cmake_minimum_required(VERSION 3.14...3.22)

project(CacheMatrixBenchmark LANGUAGES CXX)

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  VERSION 1.5.2
  OPTIONS "BENCHMARK_ENABLE_TESTING Off"
)

CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 8.1.1
)

if(benchmark_ADDED)
  set_target_properties(benchmark PROPERTIES CXX_STANDARD 17)
endif()

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

CPMAddPackage(NAME CacheMatrix SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..) # CacheMatrix::CacheMatrix
target_link_libraries(${PROJECT_NAME} CacheMatrix::CacheMatrix benchmark fmt)
