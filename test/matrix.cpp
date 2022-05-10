#include <gtest/gtest.h>

#include <OAC/cache/matrix.hpp>
#include <OAC/utils/random.hpp>
#include <iostream>

using MatrixTypes = ::testing::Types<int32_t, float, double>;
TYPED_TEST_SUITE(MatrixTest, MatrixTypes);

// {{{1 MatrixTest fixture
template <typename T> class MatrixTest : public ::testing::Test {
protected:
  oac::cache::Matrix<T> *m1_;
  oac::cache::Matrix<T> *m2_;

  enum Type { INT32, FLOAT, DOUBLE };

  virtual void SetUp() override {
    m1_ = new oac::cache::Matrix<T>(3, 3);
    m2_ = new oac::cache::Matrix<T>(3, 3);

    m1_->fillRandom(0, 100);
    m2_->fillRandom(0, 100);
  }

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
  ASSERT_EQ(this->m1_->rows(), 3);
  ASSERT_EQ(this->m1_->cols(), 3);
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

// {{{1 MatrixTest::Transpose
TYPED_TEST(MatrixTest, Transpose) {
  oac::cache::Matrix<TypeParam> m2 = this->m1_->transpose();

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_EQ(this->m1_->at(i, j), m2.at(j, i));
    }
  }
}
// }}}1

// {{{1 MatrixTest::TransposeInPlace
TYPED_TEST(MatrixTest, TransposeInPlace) {
  using oac::cache::Matrix;
  Matrix<TypeParam> *m2 = new Matrix<TypeParam>(*this->m1_);

  this->m1_->transposeInPlace();

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_EQ(this->m1_->at(i, j), m2->at(j, i));
    }
  }
}
// }}}1

// {{{1 MatrixTest::Add
TYPED_TEST(MatrixTest, Add) {
  using oac::cache::Matrix;
  Matrix<TypeParam> m3 = *this->m1_ + *this->m2_;

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_EQ(this->m1_->at(i, j) + this->m2_->at(i, j), m3.at(i, j));
    }
  }
}
// }}}

// {{{1 MatrixTest::Sub
TYPED_TEST(MatrixTest, Sub) {
  using oac::cache::Matrix;
  Matrix<TypeParam> m3 = *this->m1_ - *this->m2_;

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m1_->cols(); j++) {
      EXPECT_EQ(this->m1_->at(i, j) - this->m2_->at(i, j), m3.at(i, j));
    }
  }
}
// }}}

// {{{1 MatrixTest::Mul
TYPED_TEST(MatrixTest, Mul) {
  using oac::cache::Matrix;
  Matrix<TypeParam> m3 = *this->m1_ * *this->m2_;

  TypeParam currentCell = TypeParam{0};

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m2_->cols(); j++) {
      for (int k = 0; k < this->m1_->cols(); k++) {
        currentCell += this->m1_->at(i, k) * this->m2_->at(k, j);
      }
      EXPECT_EQ(currentCell, m3.at(i, j));
      currentCell = TypeParam{0};
    }
  }
}
// }}}1

// {{{1 MatrixTest::TransposeMul
TYPED_TEST(MatrixTest, TransposeMul) {
  using oac::cache::Matrix;
  Matrix<TypeParam> m3 = *this->m1_ ^ *this->m2_;

  TypeParam currentCell = TypeParam{0};

  for (int i = 0; i < this->m1_->rows(); i++) {
    for (int j = 0; j < this->m2_->cols(); j++) {
      for (int k = 0; k < this->m1_->cols(); k++) {
        currentCell += this->m1_->at(i, k) * this->m2_->at(j, k);
      }
      EXPECT_EQ(currentCell, m3.at(i, j));
      currentCell = TypeParam{0};
    }
  }
}
// }}}

// {{{1 MatrixTest::DimensionError
TYPED_TEST(MatrixTest, DimensionError) {
  using oac::cache::Matrix;
  Matrix<TypeParam> *m1 = new Matrix<TypeParam>(3, 3);
  Matrix<TypeParam> *m2 = new Matrix<TypeParam>(2, 2);

  EXPECT_THROW(*m1 + *m2, std::domain_error);
}
// }}}

// vim: set foldmethod=marker:
