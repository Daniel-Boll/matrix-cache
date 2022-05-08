// #include <catch2/catch.hpp>
// #include <doctest/doctest.h>
#include <OAC/cache/matrix.hpp>
#include <gtest/gtest.h>

// TEST_CASE("Matrix") { REQUIRE(oac::cache::EXAMPLES_DIR == "assets/matrices");
// }

using namespace ::testing;

TEST(FactorialTest, HandlesZeroInput) { EXPECT_EQ(1, 1); }

TEST(Anything, BasicChecks) {
  ASSERT_TRUE(oac::cache::EXAMPLES_DIR == "assets/matrices");
}
