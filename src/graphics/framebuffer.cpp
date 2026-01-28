#include "framebuffer.hpp"

namespace KissShock{
  void FrameBuffer::Clear(){
    for(std::size_t i = 0; i < m_buffer.size(); i += 4){
      m_buffer[i] = CLEAR_COLOUR.red;
      m_buffer[i+1] = CLEAR_COLOUR.green;
      m_buffer[i+2] = CLEAR_COLOUR.blue;
      m_buffer[i+3] = CLEAR_COLOUR.alpha;
    }
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
