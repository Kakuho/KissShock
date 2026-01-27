#include <array>
#include <cstddef>
#include <cstdint>

namespace KissShock{
  struct Bitmap{
    static constexpr std::size_t WIDTH = 32;
    static constexpr std::size_t HEIGHT = 32;
    std::array<std::uint8_t, WIDTH*HEIGHT> pixels;
  };
}
