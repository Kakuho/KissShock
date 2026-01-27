#pragma once

#include <cstdint>

namespace KissShock{
  struct Pixel{
    // would perf be better if we packed the components into a std::uint32_t?
    // should just move the value into a 32-bit register
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
  };
}
