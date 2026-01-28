#include "bitmap.hpp"

namespace KissShock{
  void Bitmap::PrintData() const{
    for(std::size_t i = 0; i < m_pixels.size(); i += 4){
      std::println("{:#04x} {:#04x} {:#04x} {:#04x}", 
          m_pixels[i], m_pixels[i+1], m_pixels[i+2], m_pixels[i+3]);
    }
  }
  
}
