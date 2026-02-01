#pragma once

#include <vector>
#include <optional>

#include "bitmap.hpp"

namespace KissShock{
  class Sprite{
    public:
      Sprite() = default;
      Sprite(const Bitmap& initialBitmap);
      Sprite(Bitmap&& initialBitmap){m_frames[0] = std::move(initialBitmap);}

      std::size_t Height() const noexcept{ return m_height;}
      std::size_t Width() const noexcept{ return m_width;}
      std::size_t Frames() const noexcept{return m_frames.size();}

      const Bitmap* GetFrame(std::size_t index){ 
        // would be nice if std::expected or std::optional supports reference types
        return &m_frames[index];
      }

    private:
      std::vector<Bitmap> m_frames; 
      std::size_t m_height;
      std::size_t m_width;
  };
}
