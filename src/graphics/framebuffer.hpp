#pragma once

// we're doing software rasterisation so we manage the framebuffer ourselves

#include <array>
#include <cstdint>

#include "pixel.hpp"
#include "util.hpp"

namespace KissShock{
  class FrameBuffer{
    static constexpr std::size_t HEIGHT = 320;
    static constexpr std::size_t WIDTH = 200;
    static constexpr Pixel CLEAR_COLOUR = Pixel{0xF2, 0x9E, 0xC8, 0xFF};
    public:
      std::uint8_t* Get(){return &m_buffer[0];}

      void WritePixel(Vec2<unsigned> pos, Pixel val);

      void Fill(std::uint8_t val){m_buffer.fill(val);}
      void FillPixels(Pixel pixels);

    private:
      std::array<std::uint8_t, 320 * 200 * 4> m_buffer;
  };
};
