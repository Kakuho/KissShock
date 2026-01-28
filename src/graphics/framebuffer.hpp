#pragma once

//  we're doing software rasterisation so we manage the framebuffer ourselves
//  screen coordinates starts from (0, 0) in the top left and goes to (height, width)
//  in the bottom right

#include <array>
#include <cstdint>

#include "pixel.hpp"
#include "util.hpp"
#include "bitmap.hpp"

namespace KissShock{
  class FrameBuffer{
    static constexpr std::size_t HEIGHT = 320;
    static constexpr std::size_t WIDTH = 200;
    static constexpr Pixel CLEAR_COLOUR = Pixel{0xF2, 0x9E, 0xC8, 0xFF};
    public:
      std::uint8_t* Get(){return &m_buffer[0];}

      template<typename T>
      void WritePixel(Vec2<T> pos, Pixel val){
        std::size_t pixelBase = pos.x + pos.y * HEIGHT;
        m_buffer[pixelBase] = val.red;
        m_buffer[pixelBase + 1] = val.green;
        m_buffer[pixelBase + 2] = val.blue;
        m_buffer[pixelBase + 3] = val.alpha;
      }

      void Fill(std::uint8_t val){m_buffer.fill(val);}
      void FillPixels(Pixel pixels);

      template<typename T>
      void DrawBitmap(Vec2<T> startPos, const Bitmap& bitmap){
        for(std::size_t y = 0; y < bitmap.Height(); y++){
          for(std::size_t x = 0; x < bitmap.Width(); x++){
            WritePixel(Vec2{x, y}, 
                bitmap.PixelAt(Vec2{x, y}));
          }
        }
      }

    private:
      std::array<std::uint8_t, 320 * 200 * 4> m_buffer;
  };
};
