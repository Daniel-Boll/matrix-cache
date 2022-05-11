#include <OAC/utils/random.hpp>

namespace oac {
  namespace utils {

    Random::Random(int32_t min, int32_t max)
        : _randomDevice(), _generator(_randomDevice()), _distribution(min, max) {}

    double Random::next() { return _distribution(_generator); }
    double Random::operator()() { return next(); }

  }  // namespace utils
}  // namespace oac
