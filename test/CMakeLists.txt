cmake_minimum_required(VERSION 3.14...3.22)

project(CacheMatrixTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

# =================== Choose your test framework =====================
# --------------------------------------------------------------------#
#                          google/googletest                          #
# --------------------------------------------------------------------#
CPMAddPackage("gh:google/googletest#release-1.11.0@v1.11.0")

# --------------------------------------------------------------------#
#                           catchorg/Catch2                           #
# --------------------------------------------------------------------#
# CPMAddPackage("gh:catchorg/Catch2@2.13.9")

# --------------------------------------------------------------------#
#                            onqtam/doctest                           #
# --------------------------------------------------------------------#
# CPMAddPackage("gh:onqtam/doctest@2.4.8")
# ====================================================================

if(TEST_INSTALLED_VERSION)
  find_package(CacheMatrix REQUIRED)
else()
  CPMAddPackage(NAME CacheMatrix SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
foreach(source ${sources})
  message(STATUS "Adding ${source}")
endforeach()


# @IF DOCTEST uncomment the below line
# target_link_libraries(${PROJECT_NAME} doctest::doctest CacheMatrix::CacheMatrix)
# @IF CATCH2 uncomment the below line
# target_link_libraries(${PROJECT_NAME} Catch2 CacheMatrix::CacheMatrix)
# @IF GOOGLETEST uncomment the below lines
target_link_libraries(${PROJECT_NAME} CacheMatrix::CacheMatrix gtest_main)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # target_compile_options(CacheMatrix PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(CacheMatrix PUBLIC /W4 /WX)
    # @IF DOCTEST uncomment the below line
    # target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add CacheMatrixTests ----

enable_testing()

# @IF DOCTEST uncomment the below lines
# include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
# doctest_discover_tests(${PROJECT_NAME})

# @IF {CATCH2,GOOGLETEST} uncomment the below line
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(CacheMatrix PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(CacheMatrix PUBLIC -fprofile-arcs -ftest-coverage)
endif()
