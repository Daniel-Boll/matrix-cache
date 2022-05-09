#include <fmt/core.h>
#include <gtest/gtest.h>

#include <OAC/cache/matrix.hpp>
#include <OAC/utils/random.hpp>

using MatrixTypes = ::testing::Types<int32_t, float, double>;
TYPED_TEST_SUITE(MatrixTest, MatrixTypes);

// {{{1 MatrixTest fixture
template <typename T> class MatrixTest : public ::testing::Test {
protected:
  oac::cache::Matrix<T> *m1_;
  oac::cache::Matrix<T> *m2_;

  enum Type { INT32, FLOAT, DOUBLE };

  virtual void SetUp() override { m1_ = new oac::cache::Matrix<T>(2, 2); }

  virtual void TearDown() override { delete m1_; }

  T fillZeroBasedOnType() {
    if (std::is_same<T, int32_t>::value) {
      return 0;
    } else if (std::is_same<T, float>::value) {
      return 0.0f;
    } else if (std::is_same<T, double>::value) {
      return 0.0f;
    } else {
      return 0;
    }
  }
};
// }}}1

// {{{1 CacheModule::GlobalThings
TEST(CacheModule, GlobalThings) { ASSERT_TRUE(oac::cache::EXAMPLES_DIR == "assets/matrices"); }
// }}}1

// {{{1 MatrixTest::Size
TYPED_TEST(MatrixTest, Size) {
  ASSERT_EQ(this->m1_->rows(), 2);
  ASSERT_EQ(this->m1_->cols(), 2);
}
// }}}1

// {{{1 MatrixTest::Fill
TYPED_TEST(MatrixTest, FillZero) {
  this->m1_->fill(0);

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_EQ(this->m1_->at(i, j), this->fillZeroBasedOnType())
          << "at(" << i << ", " << j << ") = " << this->m1_->at(i, j);
    }
  }
}
// }}}1

// {{{1 MatrixTest::FillRandom
TYPED_TEST(MatrixTest, FillRandom) {
  this->m1_->fillRandom(0, 100);

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_GE(this->m1_->at(i, j), 0);
      EXPECT_LE(this->m1_->at(i, j), 100);
    }
  }
}
// }}}1

// vim: set foldmethod=marker:
