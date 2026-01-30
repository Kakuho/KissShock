#pragma once

//  we're doing software rasterisation so we manage the framebuffer ourselves
//
//  screen coordinates starts from (0, 0) in the top left and goes to (height, width)
//  in the bottom right
//
//  Framebuffer will always be in screen coordinate space

#include <array>
#include <cstdint>
#include <stdexcept>

#include "pixel.hpp"
#include "util.hpp"
#include "bitmap.hpp"
#include "config.hpp"

namespace KissShock{
  class FrameBuffer{
    static constexpr std::size_t HEIGHT = Config::WINDOW_HEIGHT;
    static constexpr std::size_t WIDTH = Config::WINDOW_WIDTH;
    static constexpr Pixel CLEAR_COLOUR = Pixel{0xF2, 0x9E, 0xC8, 0xFF};
    public:
      FrameBuffer(){FillPixels(CLEAR_COLOUR);}
      std::uint8_t* Get(){return &m_buffer[0];}

      consteval std::size_t Size(){ return HEIGHT * WIDTH * 4;}
      consteval std::size_t Dimensions(){ return HEIGHT * WIDTH;}

      template<typename T>
      void WritePixel(Vec2<T> pos, Pixel val){
        std::size_t pixelBase = (pos.x + pos.y * WIDTH) * 4;
        m_buffer[pixelBase] = val.red;
        m_buffer[pixelBase + 1] = val.green;
        m_buffer[pixelBase + 2] = val.blue;
        m_buffer[pixelBase + 3] = val.alpha;
      }

      template<typename T>
      void ClearPixel(Vec2<T> pos){
        std::size_t pixelBase = (pos.x + pos.y * WIDTH) * 4;
        m_buffer[pixelBase] = CLEAR_COLOUR.red;
        m_buffer[pixelBase + 1] = CLEAR_COLOUR.green;
        m_buffer[pixelBase + 2] = CLEAR_COLOUR.blue;
        m_buffer[pixelBase + 3] = CLEAR_COLOUR.alpha;
      }

      void Clear();
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

      template<typename T>
      void DrawHorizontalLine(Vec2<T> start, int length, Pixel val);

      template<typename T>
      void DrawVerticalLine(Vec2<T> start, int length, Pixel val);

      template<typename T>
      void DrawRectangle(Vec2<T> start, Vec2<T> end, Pixel val);
        // start is the coordinate for top left, end is the bottom right coordinate

    private:
      std::array<std::uint8_t, HEIGHT * WIDTH * 4> m_buffer;
  };

  // Impl

  template<typename T>
  void FrameBuffer::DrawHorizontalLine(Vec2<T> start, int length, Pixel val){
    if(length < 0){
      for(int i = 0; i > length; i--){
        WritePixel(Vec2{start.x + i, start.y}, val);
      }
    }
    else{
      for(int i = 0; i < length; i++){
        WritePixel(Vec2{start.x + i, start.y}, val);
      }
    }
  }

  template<typename T>
  void FrameBuffer::DrawVerticalLine(Vec2<T> start, int length, Pixel val){
    if(length < 0){
      for(int i = 0; i > length; i--){
        WritePixel(Vec2{start.x, start.y + i}, val);
      }
    }
    else{
      for(int i = 0; i < length; i++){
        WritePixel(Vec2{start.x, start.y + i}, val);
      }
    }
  }

  template<typename T>
  void FrameBuffer::DrawRectangle(Vec2<T> start, Vec2<T> end, Pixel val){
    if(start.x > end.x || start.y > end.y){
      throw std::runtime_error{"Error: FrameBuffer::DrawRectangle(...) start.x > end.x or start.y > end.y"};
    }
    std::size_t length = end.x - start.x;
    for(std::size_t i = start.y; i < end.y; i++){
      DrawHorizontalLine(Vec2<std::size_t>{start.x, start.y+i}, length, val);
    }
  }

};
