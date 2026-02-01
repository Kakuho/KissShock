#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string_view>
#include <print>
#include <fstream>

#include "util.hpp"
#include "graphics/pixel.hpp"

namespace KissShock{
  class Bitmap{
    public:
      Bitmap(std::size_t height, std::size_t width, std::vector<std::uint8_t>&& data)
        :
          m_height{height},
          m_width{width},
          m_pixels{std::move(data)}
      {

      }

      constexpr std::size_t Height() const noexcept{ return m_height;}
      constexpr std::size_t Width() const noexcept{ return m_width;}
      
      template<typename T>
      Pixel PixelAt(Vec2<T> pos) const{
        std::size_t pixelBase = (pos.x + pos.y * Width()) * 4;
        auto red = m_pixels[pixelBase];
        auto green = m_pixels[pixelBase+1];
        auto blue = m_pixels[pixelBase+2];
        auto alpha = m_pixels[pixelBase+3];
        return {red, green, blue, alpha};
      }

      void PrintData() const;
      
      void DumpAsPpm(std::string_view filepath) const;
  
    private:
      std::size_t m_height;
      std::size_t m_width;
      std::vector<std::uint8_t> m_pixels;
  };
}
