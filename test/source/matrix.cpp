// #include <catch2/catch.hpp>
// #include <doctest/doctest.h>
#include <gtest/gtest.h>
#include <OAC/cache/matrix.hpp>

// TEST_CASE("Matrix") { REQUIRE(oac::cache::EXAMPLES_DIR == "assets/matrices"); }

TEST(CacheMatrixTests, BasicChecks) { ASSERT_TRUE(oac::cache::EXAMPLES_DIR == "assets/matrices"); }
