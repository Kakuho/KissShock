#pragma once

//  for now we support QOI but later i will add more file formats
//
//  https://en.wikipedia.org/wiki/QOI_(image_format)
//
//  Deocode() will return a std::vector<std::uint8_t> containing the decoded image pixels

#include <array>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string_view>
#include <fstream>
#include <print>
#include <cstring>
#include <expected>
#include <bit>
#include <ranges>
#include <algorithm>
#include <cassert>

#include "graphics/bitmap.hpp"
#include "graphics/pixel.hpp"

inline void PrintPixelBuffer(std::vector<std::uint8_t>& buffer){
  std::println("Size: {}", buffer.size());
  for(std::size_t i = 0; i < buffer.size(); i += 4){
    std::println("{:#02x}{:02x}{:02x}{:02x}", buffer[i], buffer[i+1], buffer[i+2], buffer[i+3]);
  }
}

namespace KissShock{
  class QoiLoader{
    static constexpr std::array<char, 4> MAGIC = {'q', 'o', 'i', 'f'};
    static constexpr Pixel INITIAL_PIXEL = {0, 0, 0, 255};
    static constexpr std::array<std::uint8_t, 8> END_BLOCK = 
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

    static constexpr std::size_t DATA_START = 14;

    enum class LoaderError{
      MAGIC_FAILED,
      UNKOWN_CHUNK,
      DECODE_FAILED
    };

    enum class DataChunkType: std::uint8_t{
      RGB = 0xFE,
      RGBA = 0xFF,
      RUN = 0b1100'0000,
      INDEX = 0b0000'0000,
      DIFF = 0b0100'0000,
      LUMA = 0b1000'0000
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

      static constexpr std::size_t Hash(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a){
        std::size_t val = r*3;
        val += g*5;
        val += b*7;
        val += a*11;
        val %= 64;
        return val;
        //return (r * 3 + g * 5 + b * 7 + a * 11) % 64;
      }

      static constexpr std::size_t Hash(Pixel& p){
        return Hash(p.red, p.green, p.blue, p.alpha);
      }

      void SetLastPixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha);
      void SetLastPixel(Pixel pixel);
      
      void PrintDetails() const;
      void PrintBuffer() const;
      bool IsEndBlock(std::size_t index) const;
      std::expected<std::vector<std::uint8_t>, LoaderError> Decode();
      std::expected<Bitmap, QoiLoader::LoaderError> GenerateBitmap();

    private:
      void IsValid() const;
      void InitHeader();

      void HandleRGBChunk(std::vector<std::uint8_t>& output);
      void HandleRGBAChunk(std::vector<std::uint8_t>& output);
      void HandleIndexChunk(std::vector<std::uint8_t>& output);

      void HandleDiffChunk(std::vector<std::uint8_t>& output){
        throw std::runtime_error{"QoiLoader::HandleDiffChunk(...) Unimplemented"};
      }

      void HandleLumaChunk(std::vector<std::uint8_t>& output){
        throw std::runtime_error{"QoiLoader::HandleLumaChunk(...) Unimplemented"};
      }

      void HandleRunChunk(std::vector<std::uint8_t>& output);

      QoiHeader m_header;
      std::size_t m_pos;
      Pixel m_lastPixel;
      std::vector<std::uint8_t> m_buffer;
      std::array<Pixel, 64> m_prevpixels;
  };
}
