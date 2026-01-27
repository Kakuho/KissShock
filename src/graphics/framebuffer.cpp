#include "framebuffer.hpp"

namespace KissShock{
  void FrameBuffer::WritePixel(Vec2<unsigned> pos, Pixel val){
    std::size_t pixelBase = pos.x + pos.y * HEIGHT;
    m_buffer[pixelBase] = val.red;
    m_buffer[pixelBase + 1] = val.green;
    m_buffer[pixelBase + 2] = val.blue;
    m_buffer[pixelBase + 3] = val.alpha;
  }
  

  void FrameBuffer::FillPixels(Pixel pixel){
    for(std::size_t i = 0; i < m_buffer.size(); i += 4){
      m_buffer[i] = pixel.red;
      m_buffer[i+1] = pixel.green;
      m_buffer[i+2] = pixel.blue;
      m_buffer[i+3] = pixel.alpha;
    }
  }
}
