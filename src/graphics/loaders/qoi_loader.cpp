#include "qoi_loader.hpp"
#include <fstream>

namespace KissShock{
  QoiLoader::QoiLoader(std::string_view filename){
    std::basic_ifstream<std::uint8_t> ifst{filename.data(), std::ios_base::ate};
    std::size_t size = ifst.tellg();
    ifst.seekg(0);
    // read the data into some buffer
    std::uint8_t raw[size];
    ifst.readsome(raw, size);
    m_buffer = std::move(std::vector<std::uint8_t>{raw, raw+size});
  }
}
