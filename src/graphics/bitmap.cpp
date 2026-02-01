#include "bitmap.hpp"
#include <fstream>

namespace KissShock{
  void Bitmap::PrintData() const{
    std::println("Printing Bitmap Data...");
    for(std::size_t i = 0; i < m_pixels.size(); i += 4){
      std::println("{:#04x}{:02x}{:02x}{:02x}", 
          m_pixels[i], m_pixels[i+1], m_pixels[i+2], m_pixels[i+3]);
    }
    std::println("Printing in matrix form...");
    for(std::size_t j = 0; j < Height(); j++){
      for(std::size_t i = 0; i < Width(); i++){
        auto pixel = PixelAt(Vec2{i, j});
        std::println("{:#04x}{:02x}{:02x}{:02x}", pixel.red, pixel.blue, pixel.green, pixel.alpha);
      }
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
