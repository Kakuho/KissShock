#pragma once

// for now we support QOI but later i will add more file formats
//
// https://en.wikipedia.org/wiki/QOI_(image_format)

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>
#include <fstream>
#include <print>

namespace KissShock{
  class QoiLoader{
    public:
      QoiLoader(std::string_view filename);
      
      void PrintBuffer() const;

    private:
      void IsValid() const;
      
      std::vector<std::uint8_t> m_buffer;
      std::array<std::uint8_t, 64> m_prevpixels;
  };
}
