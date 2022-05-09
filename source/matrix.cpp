#include <fmt/format.h>

#include <OAC/cache/matrix.hpp>
#include <OAC/utils/random.hpp>
#include <iostream>

namespace oac {
  namespace cache {
    //------------------------------------------------------------------//
    //                           Constructor                            //
    //------------------------------------------------------------------//
    template <typename T> Matrix<T>::Matrix(int32_t rows, int32_t cols) : _rows(rows), _cols(cols) {
      this->reserve();
    }

    template <typename T> Matrix<T>::Matrix(int32_t rows, int32_t cols, T value)
        : _rows(rows), _cols(cols) {
      this->reserve();
      this->fill(value);
    }

    //------------------------------------------------------------------//
    //                         Private members                          //
    //------------------------------------------------------------------//
    template <typename T> void Matrix<T>::reserve() {
      _data = new T*[_rows];
      for (int32_t i = 0; i < _rows; i++) {
        _data[i] = new T[_cols];
      }
    }

    //------------------------------------------------------------------//
    //                          Public members                          //
    //------------------------------------------------------------------//

    template <typename T> int32_t Matrix<T>::rows() const { return _rows; }
    template <typename T> int32_t Matrix<T>::cols() const { return _cols; }

    // \\-=-----------------------------------------------------------------=//
    //                               Accessors
    template <typename T> const T& Matrix<T>::operator()(int32_t row, int32_t col) const {
      return _data[row][col];
    }

    template <typename T> T& Matrix<T>::operator()(int32_t row, int32_t col) {
      return _data[row][col];
    }

    template <typename T> const T& Matrix<T>::at(int32_t row, int32_t col) const {
      return _data[row][col];
    }

    template <typename T> T& Matrix<T>::at(int32_t row, int32_t col) { return _data[row][col]; }
    // \\-=-----------------------------------------------------------------=//

    template <typename T> void Matrix<T>::fill(T value) {
      for (int32_t row = 0; row < _rows; row++) {
        for (int32_t col = 0; col < _cols; col++) {
          _data[row][col] = value;
        }
      }
    }

    template <typename T> void Matrix<T>::fillRandom(int32_t min, int32_t max) {
      for (int32_t row = 0; row < _rows; row++)
        for (int32_t col = 0; col < _cols; col++)
          _data[row][col] = oac::utils::randomBetween(min, max);
    }

  }  // namespace cache
}  // namespace oac

// Define possible instantiations of Matrix
template class oac::cache::Matrix<int32_t>;
template class oac::cache::Matrix<float>;
template class oac::cache::Matrix<double>;
