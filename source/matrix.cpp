#include <fmt/format.h>

#include <OAC/cache/matrix.hpp>

namespace oac {
  namespace cache {
    Matrix::Matrix(int32_t rows, int32_t cols) : _rows(rows), _cols(cols) {}

    int32_t Matrix::rows() const { return _rows; }
    int32_t Matrix::cols() const { return _cols; }
  }  // namespace cache
}  // namespace oac
