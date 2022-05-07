#include <fmt/core.h>

#include <OAC/cache/matrix.hpp>

auto main(int argc, char** argv) -> int {
  // using namespace oac::cache;
  // Matrix<double> matrix(2, 2);
  fmt::print("Hello world\n");
  fmt::print("{}\n", oac::cache::EXAMPLES_DIR);

  // fmt::print("{} {}\n", matrix->rows(), matrix->cols());

  return 0;
}
