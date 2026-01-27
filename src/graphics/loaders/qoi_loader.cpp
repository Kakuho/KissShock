#include "qoi_loader.hpp"
#include <bit>
#include <fstream>

namespace KissShock{
  QoiLoader::QoiLoader(std::string_view filename){
    std::ifstream ifst{filename.data(), std::ios_base::ate};
    std::size_t size = ifst.tellg();
    ifst.seekg(0);
    // read the data into some buffer
    char raw[size];
    ifst.readsome(raw, size);
    m_buffer = std::move(std::vector<std::uint8_t>{raw, raw+size});
    InitHeader();
  }

  void QoiLoader::PrintDetails() const{
    std::print("Header Magic: ");
    for(int i = 0; i < m_header.header.size(); i++){
      std::print("{}", m_header.header[i]);
    }
    std::println();
    std::println("Width: {}", m_header.width);
    std::println("Height: {}", m_header.height);
    std::println("Channels: {}", m_header.channels);
    std::println("ColourSpace: {}", m_header.colourspace);
  }

  void QoiLoader::PrintBuffer() const{
    for(int i = 1; i < m_buffer.size() +1; i++){
      std::print("{:#04x} ", m_buffer[i-1]);
      if(i % 16 == 0){
        std::println("");
      }
    }
  }

  void QoiLoader::InitHeader(){
    std::memcpy(&m_header, m_buffer.data(), 14);
    // the width and height are stored in big endian order so we need to perfom byte reversing on intel
    m_header.width = std::byteswap(m_header.width);
    m_header.height = std::byteswap(m_header.height);
  }
  
  std::expected<std::vector<std::uint8_t>, QoiLoader::LoaderError> QoiLoader::Decode() const{
    std::vector<std::uint8_t> output;
  }

}
