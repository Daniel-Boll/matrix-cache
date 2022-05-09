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
      Matrix(const std::string &filepath);

      const T &operator()(int32_t row, int32_t col) const;
      T &operator()(int32_t row, int32_t col);

      const T &at(int32_t row, int32_t col) const;
      T &at(int32_t row, int32_t col);

      void fill(T value);
      void fillRandom(int32_t min, int32_t max);

      int32_t rows() const;
      int32_t cols() const;
    };
  }  // namespace cache
}  // namespace oac
