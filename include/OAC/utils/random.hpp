#pragma once

#include <OAC/common.hpp>

namespace oac {
  namespace utils {
    class Random {
    private:
      std::random_device _randomDevice;
      std::mt19937 _generator;
      std::uniform_int_distribution<> _distribution;

    public:
      Random(int32_t min, int32_t max);

      double next();
      double operator()();
    };
  }  // namespace utils
}  // namespace oac
