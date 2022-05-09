#pragma once

#include <OAC/common.hpp>

#define matrix_index(i, j) i* columns + j

namespace oac {
  namespace cache {
    template <typename T> class MatrixFlat {
    private:
      int32_t _rows, _cols;

      /**                                 Why use only one vector?
        ┌─────────────────────────────────────────────────────────────────────────────────────────┐
        │You can improve performance by using one vector instead of two vectors; you can calculate│
        │the 2nd dimension using a little math. This is actually how primitive 2D arrays work in  │
        │C++.                                                                                     │
        │                                                                                         │
        │Advantages:                                                                              │
        │    ~ Elements stay in contiguous storage, as opposed to linked-list-like structure where│
        │every row leads to an entirely different memory (in terms of adjacency). This is         │
        │beneficial for the cache.                                                                │
        │    ~ Easy to implement                                                                  │
        │                                                                                         │
        │Disadvantages:                                                                           │
        │    ~ You can no longer use the idiomatic matrix[i][j] syntax, thus you must provide your│
        │own access operator.                                                                     │
        │                                                                                         │
        │                                                                                         │
        │                        https://codereview.stackexchange.com/a/142834                    │
        └─────────────────────────────────────────────────────────────────────────────────────────┘
       */
      std::vector<T> _data;

    public:
      using value_type = typename std::vector<T>::value_type;
      using reference = typename std::vector<T>::reference;
      using size_type = typename std::vector<T>::size_type;

      MatrixFlat(int32_t rows, int32_t cols);

      int32_t rows() const;
      int32_t cols() const;
    };
  }  // namespace cache
}  // namespace oac
