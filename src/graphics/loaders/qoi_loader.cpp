#include "qoi_loader.hpp"
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
  }

  void QoiLoader::PrintDetails() const{
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
  }
  
  std::vector<std::uint8_t> QoiLoader::Decode() const{
    std::vector<std::uint8_t> output;
  }

}
