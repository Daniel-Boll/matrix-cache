#include <fmt/format.h>

#include <OAC/cache/matrix.hpp>
#include <OAC/utils/random.hpp>
#include <stdexcept>

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

    template <typename T> Matrix<T>::Matrix(const Matrix<T>& other)
        : _rows(other._rows), _cols(other._cols) {
      this->reserve();

      for (int32_t i = 0; i < other._rows; i++)
        for (int32_t j = 0; j < other._cols; j++) _data[i][j] = other._data[i][j];
    }

    template <typename T> Matrix<T>::~Matrix() {
      for (int32_t i = 0; i < this->_rows; i++) delete[] _data[i];

      delete[] _data;
    }

    //------------------------------------------------------------------//
    //                         Private members                          //
    //------------------------------------------------------------------//
    template <typename T> void Matrix<T>::reserve() {
      _data = new T*[_rows];
      for (int32_t i = 0; i < _rows; i++) _data[i] = new T[_cols];
    }

    //------------------------------------------------------------------//
    //                          Public members                          //
    //------------------------------------------------------------------//

    template <typename T> int32_t Matrix<T>::rows() const { return _rows; }
    template <typename T> int32_t Matrix<T>::cols() const { return _cols; }

    template <typename T> void Matrix<T>::fill(T value) {
      for (int32_t row = 0; row < _rows; row++)
        for (int32_t col = 0; col < _cols; col++) _data[row][col] = value;
    }

    // Operators
    template <typename T> Matrix<T>& Matrix<T>::operator+(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T>* temporaryMatrix = new Matrix<T>(_rows, other._cols);

      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < other._cols; j++)
          temporaryMatrix->_data[i][j] = _data[i][j] + other._data[i][j];

      return *temporaryMatrix;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator-(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T>* temporaryMatrix = new Matrix<T>(_rows, other._cols);

      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < other._cols; j++)
          temporaryMatrix->_data[i][j] = _data[i][j] - other._data[i][j];

      return *temporaryMatrix;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator/(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T>* temporaryMatrix = new Matrix<T>(_rows, other._cols);

      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < other._cols; j++)
          for (int32_t k = 0; k < _cols; k++)
            temporaryMatrix->_data[i][j] += _data[i][k] / other._data[k][j];

      return *temporaryMatrix;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator*(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T>* temporaryMatrix = new Matrix<T>(_rows, other._cols);

      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < other._cols; j++)
          for (int32_t k = 0; k < _cols; k++)
            temporaryMatrix->_data[i][j] += _data[i][k] * other._data[k][j];

      return *temporaryMatrix;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator^(const Matrix<T>& other) {
      if (_rows != other._cols || _cols != other._rows)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T>* temporaryMatrix = new Matrix<T>(_rows, other._cols);

      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < other._cols; j++)
          for (int32_t k = 0; k < _cols; k++)
            temporaryMatrix->_data[i][j] += _data[i][k] * other._data[j][k];

      return *temporaryMatrix;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
      if (this == &other) return *this;

      _rows = other._rows;
      _cols = other._cols;
      for (int32_t i = 0; i < _rows; i++)
        for (int32_t j = 0; j < _cols; j++) _data[i][j] = other._data[i][j];

      return *this;
    }

    template <typename T> Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T> temporaryMatrix = *this * other;

      return (*this = temporaryMatrix);
    }

    template <typename T> Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T> temporaryMatrix = *this / other;

      return (*this = temporaryMatrix);
    }

    template <typename T> Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T> temporaryMatrix = *this - other;

      return (*this = temporaryMatrix);
    }

    template <typename T> Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
      if (_rows != other._rows || _cols != other._cols)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T> temporaryMatrix = *this + other;

      return (*this = temporaryMatrix);
    }

    template <typename T> Matrix<T>& Matrix<T>::operator^=(const Matrix<T>& other) {
      if (_rows != other._cols || _cols != other._rows)
        throw std::domain_error(fmt::format("Matrix dimensions do not match: {}x{} vs {}x{}", _rows,
                                            _cols, other._rows, other._cols));

      Matrix<T> temporaryMatrix = *this ^ other;

      return (*this = temporaryMatrix);
    }

    template <typename T> void Matrix<T>::fillRandom(int32_t min, int32_t max) {
      for (int32_t row = 0; row < _rows; row++)
        for (int32_t col = 0; col < _cols; col++)
          _data[row][col] = oac::utils::randomBetween(min, max);
    }

    template <typename T> void Matrix<T>::transposeInPlace() {
      T** newData = new T*[_cols];
      for (int32_t i = 0; i < _cols; i++) {
        newData[i] = new T[_rows];
      }

      for (int32_t row = 0; row < _rows; row++) {
        for (int32_t col = 0; col < _cols; col++) {
          newData[col][row] = _data[row][col];
        }
      }

      for (int32_t i = 0; i < _rows; i++) {
        delete[] _data[i];
      }
      delete[] _data;

      _data = newData;

      int32_t tmp = _rows;
      _rows = _cols;
      _cols = tmp;

      return;
    }

    template <typename T> Matrix<T> Matrix<T>::transpose() const {
      Matrix<T> result(_cols, _rows);

      for (int32_t row = 0; row < _rows; row++) {
        for (int32_t col = 0; col < _cols; col++) {
          result(col, row) = _data[row][col];
        }
      }

      return result;
    }

  }  // namespace cache
}  // namespace oac

// Define possible instantiations of Matrix
template class oac::cache::Matrix<int32_t>;
template class oac::cache::Matrix<float>;
template class oac::cache::Matrix<double>;
