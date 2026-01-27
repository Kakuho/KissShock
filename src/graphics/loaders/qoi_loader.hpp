#pragma once

//  for now we support QOI but later i will add more file formats
//
//  https://en.wikipedia.org/wiki/QOI_(image_format)
//
//  Deocode() will return a std::vector<std::uint8_t> containing the decoded image pixels

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>
#include <fstream>
#include <print>

namespace KissShock{
  class QoiLoader{

    struct QoiHeader{
      std::uint8_t header[4];
      std::uint32_t width;
      std::uint32_t height;
      std::uint8_t channels;
      std::uint8_t colourspace;
    };

    public:
      QoiLoader(std::string_view filename);
      
      void PrintBuffer() const;
      std::vector<std::uint8_t> Decode() const;

    private:
      void IsValid() const;
      
      std::vector<std::uint8_t> m_buffer;
      std::array<std::uint8_t, 64> m_prevpixels;
  };
}
