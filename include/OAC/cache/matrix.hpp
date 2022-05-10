#pragma once

#include <OAC/common.hpp>

namespace oac {
  namespace cache {
    const std::string EXAMPLES_DIR = "assets/matrices";

    template <typename T> class Matrix {
    private:
      int32_t _rows, _cols;
      T **_data;

      void reserve();

    public:
      Matrix(int32_t rows, int32_t cols);
      Matrix(int32_t rows, int32_t cols, T value);
      Matrix(const Matrix<T> &other);
      ~Matrix();

      // Acessors
      inline constexpr T &operator()(int32_t row, int32_t col) const { return _data[row][col]; }
      inline constexpr T &operator()(int32_t row, int32_t col) { return _data[row][col]; }
      inline constexpr T &at(int32_t row, int32_t col) const { return _data[row][col]; }
      inline constexpr T &at(int32_t row, int32_t col) { return _data[row][col]; }

      // Operators
      Matrix<T> &operator+(const Matrix<T> &other);
      Matrix<T> &operator-(const Matrix<T> &other);
      Matrix<T> &operator/(const Matrix<T> &other);
      Matrix<T> &operator*(const Matrix<T> &other);
      Matrix<T> &operator^(const Matrix<T> &other);

      Matrix<T> &operator=(const Matrix<T> &other);

      Matrix<T> &operator+=(const Matrix<T> &other);
      Matrix<T> &operator-=(const Matrix<T> &other);
      Matrix<T> &operator/=(const Matrix<T> &other);
      Matrix<T> &operator*=(const Matrix<T> &other);
      Matrix<T> &operator^=(const Matrix<T> &other);

      void fill(T value);
      void fillRandom(int32_t min, int32_t max);

      void transposeInPlace();
      [[nodiscard]] Matrix<T> transpose() const;

      int32_t rows() const;
      int32_t cols() const;
    };
  }  // namespace cache
}  // namespace oac
