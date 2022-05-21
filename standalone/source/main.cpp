#include <fmt/core.h>

#include <OAC/cache/matrix.hpp>
#include <cxxopts.hpp>
#include <iterator>

#define BREAK_LINE fmt::print("\n")

using matricesStore = std::vector<std::unique_ptr<oac::cache::Matrix<double>>>;

// NOTE: for now we only support two matrix
// TODO: add support for pairing
static const void calculateMultiplications(const matricesStore& matrices, bool transpose) {
  using oac::cache::Matrix;
  fmt::print("Shall I transpose the matrices? {}\n", transpose ? "Yes" : "No");

  // Extract first and second matrix
  const auto& first = matrices[0];
  const auto& second = matrices[1];

  // fmt::print("{}x{} {} {}x{}\n", first->rows(), first->cols(), transpose ? "^" : "*",
  //            transpose ? second->transpose().rows() : second->rows(),
  //            transpose ? second->transpose().cols() : second->cols());

  first->fillRandom(0, 2);
  second->fillRandom(0, 2);

  // first->print();
  // BREAK_LINE;
  // second->print();
  // BREAK_LINE;

  Matrix<double> result = transpose ? *first ^ second->transpose() : *first * *second;

  // result.print();
  // BREAK_LINE;
}

auto main(int argc, char** argv) -> int {
  cxxopts::Options options("CacheMatrix",
                           "Program that produces the multiplication of a matrix and allowing the "
                           "use to choose a better cache friendly way to handle it");

  // clang-format off
  options.add_options()
    ("m,matrix", "The matrix dimensions e.g.: 3,3", cxxopts::value<std::vector<uint32_t>>())
    ("t,transpose", "Method of multiplication set to transpose", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print help");
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    fmt::print("{}\n", options.help());
    exit(0);
  }

  using oac::cache::Matrix;

  std::vector<std::unique_ptr<Matrix<double>>> matrices;

  bool transpose = result.count("transpose") ? result["transpose"].as<bool>() : false;

  if (result.count("matrix")) {
    auto matricesDimensions = result["matrix"].as<std::vector<uint32_t>>();

    // At every pair of dimensions, we create a new matrix
    for (uint32_t i = 0; i < matricesDimensions.size(); i += 2) {
      matrices.emplace_back(
          std::make_unique<Matrix<double>>(matricesDimensions[i], matricesDimensions[i + 1]));
    }
  } else {
    matrices.emplace_back(std::make_unique<Matrix<double>>(3, 3));
    matrices.emplace_back(std::make_unique<Matrix<double>>(3, 3));
  }

  calculateMultiplications(matrices, transpose);
  return 0;
}
