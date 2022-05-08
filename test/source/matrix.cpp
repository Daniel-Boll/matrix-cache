#include <gtest/gtest.h>

#include <OAC/cache/matrix.hpp>

TEST(CacheModule, GlobalThings) { ASSERT_TRUE(oac::cache::EXAMPLES_DIR == "assets/matrices"); }

TEST(Matrix, Constructor) {
  oac::cache::Matrix m(2, 2);

  ASSERT_EQ(m.rows(), 2);
  ASSERT_EQ(m.cols(), 2);
}
