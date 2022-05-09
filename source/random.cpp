#include <OAC/utils/random.hpp>

namespace oac {
  namespace utils {
    double randomBetween(int32_t min, int32_t max) {
      // Using the Mersenne Twister algorithm
      std::random_device randomDevice;
      std::mt19937 generator(randomDevice());
      std::uniform_real_distribution<> distribution(min, max);

      return distribution(generator);
    }
  }  // namespace utils
}  // namespace oac
