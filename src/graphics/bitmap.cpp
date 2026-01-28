#include "bitmap.hpp"
#include <fstream>

namespace KissShock{
  void Bitmap::PrintData() const{
    for(std::size_t i = 0; i < m_pixels.size(); i += 4){
      std::println("{:#04x} {:#04x} {:#04x} {:#04x}", 
          m_pixels[i], m_pixels[i+1], m_pixels[i+2], m_pixels[i+3]);
    }
  }

  void Bitmap::DumpAsPpm(std::string_view filepath) const{
    auto ofst = std::ofstream{filepath.data()};
    std::println(ofst, "p3");
    std::println(ofst, "{} {}", m_width, m_height);
    std::println(ofst, "255");
    for(auto i = 0ul; i < m_pixels.size(); i+=4){
      // ignore the alpha
      std::println(ofst, "{} {} {}", m_pixels[i], m_pixels[i+1], m_pixels[i+2]);
    }
  }
}
