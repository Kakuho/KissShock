#pragma once

// for now we support QOI but later i will add more file formats
//
// https://en.wikipedia.org/wiki/QOI_(image_format)

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>
#include <fstream>

namespace KissShock{
  class QoiLoader{
    public:
      QoiLoader(std::string_view filename);

    private:
      auto IsValid() const -> bool;
      
      std::vector<std::uint8_t> m_buffer;
      std::array<std::uint8_t, 64> m_prevpixels;
  };
}
