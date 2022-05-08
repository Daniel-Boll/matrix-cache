#pragma once

#include <string>

namespace oac {
  namespace cache {
    const std::string EXAMPLES_DIR = "assets/matrices";

    class Matrix {
    private:
      int32_t _rows, _cols;

    public:
      Matrix(int32_t rows, int32_t cols);

      int32_t rows() const;
      int32_t cols() const;
    };
  }  // namespace cache
}  // namespace oac
