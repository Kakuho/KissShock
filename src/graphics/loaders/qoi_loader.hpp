#pragma once

// for now we support QOI but later i will add more file formats
//
// https://en.wikipedia.org/wiki/QOI_(image_format)

#include <array>
#include <cstdint>

namespace KissShock{
  class QoiLoader{
    public:
      QoiLoader(const char* filename);

    private:
      std::array<std::uint8_t, 64> m_prevpixels;
  };
}
