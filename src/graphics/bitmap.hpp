#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <print>

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

      void PrintData(){
        for(std::size_t i = 0; i < m_pixels.size(); i += 4){
          std::println("{:#04x} {:#04x} {:#04x} {:#04x}", m_pixels[i], m_pixels[i+1], m_pixels[i+2], m_pixels[i+3]);
        }
      }

    private:
      std::size_t m_height;
      std::size_t m_width;
      std::vector<std::uint8_t> m_pixels;
  };
}
