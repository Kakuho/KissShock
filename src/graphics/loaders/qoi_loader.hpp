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

namespace KissShock{

  struct Pixel{
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
  };

  class QoiLoader{
    static constexpr std::array<char, 4> MAGIC = {'q', 'o', 'i', 'f'};
    static constexpr std::array<std::uint8_t, 8> END_BLOCK = 
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

    static constexpr std::size_t DATA_START = 14;

    enum class LoaderError{
      MAGIC_FAILED,
      UNKOWN_CHUNK
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

      static constexpr std::uint8_t Hash(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a){
        return (r * 3 + g * 5 + b * 7 + a * 11) % 64;
      }

      static constexpr std::uint8_t Hash(Pixel& p){
        return (p.red * 3 + p.green * 5 + p.blue * 7 + p.alpha * 11) % 64;
      }
      
      void PrintDetails() const;
      void PrintBuffer() const;
      bool IsEndBlock(std::size_t index) const;
      std::expected<std::vector<std::uint8_t>, LoaderError> Decode() const;

    private:
      void IsValid() const;
      void InitHeader();

      void HandleRGBChunk(std::size_t index, std::vector<std::uint8_t>& output) const{ 
        throw std::runtime_error{"QoiLoader::HandleRGBChunk(...) Unimplemented"};
      }

      void HandleRGBAChunk(std::size_t index, std::vector<std::uint8_t>& output) const{ 
        throw std::runtime_error{"QoiLoader::HandleRGBAChunk(...) Unimplemented"};
      }

      void HandleIndexChunk(std::size_t index, std::vector<std::uint8_t>& output) const{
        throw std::runtime_error{"QoiLoader::HandleIndexChunk(...) Unimplemented"};
      }

      void HandleDiffChunk(std::size_t index, std::vector<std::uint8_t>& output) const{
        throw std::runtime_error{"QoiLoader::HandleDiffChunk(...) Unimplemented"};
      }

      void HandleLumaChunk(std::size_t index, std::vector<std::uint8_t>& output) const{
        throw std::runtime_error{"QoiLoader::HandleLumaChunk(...) Unimplemented"};
      }

      void HandleRunChunk(std::size_t index, std::vector<std::uint8_t>& output) const{
        throw std::runtime_error{"QoiLoader::HandleRunChunk(...) Unimplemented"};
      }

      QoiHeader m_header;
      std::vector<std::uint8_t> m_buffer;
      std::array<Pixel, 64> m_prevpixels;
  };
}
