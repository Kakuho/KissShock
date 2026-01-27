#pragma once

//  for now we support QOI but later i will add more file formats
//
//  https://en.wikipedia.org/wiki/QOI_(image_format)
//
//  Deocode() will return a std::vector<std::uint8_t> containing the decoded image pixels

#include <array>
#include <cmath>
#include <cstdint>
#include <vector>
#include <string_view>
#include <fstream>
#include <print>
#include <cstring>
#include <expected>
#include <bit>

namespace KissShock{
  class QoiLoader{
    static constexpr std::array<char, 4> MAGIC = {'q', 'o', 'i', 'f'};

    enum class LoaderError{
      MAGIC_FAILED
    };

    struct [[gnu::packed]] QoiHeader{
      std::array<char, 4> header;
      std::uint32_t width;
      std::uint32_t height;
      std::uint8_t channels;
      std::uint8_t colourspace;
    };
    static_assert(sizeof(QoiHeader) == 14);

    public:
      QoiLoader(std::string_view filename);
      
      void PrintDetails() const;
      void PrintBuffer() const;
      std::expected<std::vector<std::uint8_t>, LoaderError> Decode() const;

    private:
      void IsValid() const;
      void InitHeader();

      QoiHeader m_header;
      std::vector<std::uint8_t> m_buffer;
      std::array<std::uint8_t, 64> m_prevpixels;
  };
}
