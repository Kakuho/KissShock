#include "qoi_loader.hpp"
#include <bit>
#include <exception>
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

  bool QoiLoader::IsEndBlock(std::size_t index) const{
    auto currentBlock = m_buffer | std::views::drop(index) | std::views::take(8);
    return std::ranges::equal(currentBlock, END_BLOCK);
  }
  
  std::expected<std::vector<std::uint8_t>, QoiLoader::LoaderError> QoiLoader::Decode() const{
    if(m_header.header != MAGIC){
      return std::unexpected(LoaderError::MAGIC_FAILED);
    }
    std::size_t imageSize = m_header.width * m_header.height * m_header.channels;
    std::vector<std::uint8_t> output(imageSize);  // init with imageSize amount of elements
    std::size_t index = DATA_START;
    while(!IsEndBlock(index)){
      if(m_buffer[index] & 0xFE){
        HandleRGBChunk(index, output);
      }
      else if(m_buffer[index] & 0xFF){
        HandleRGBAChunk(index, output);
      }
      else if(m_buffer[index] & 0xC0){
        HandleRunChunk(index, output);
      }
      else if(!(m_buffer[index] & 0x3F)){
        HandleIndexChunk(index, output);
      }
      else if(m_buffer[index] & 0x40){
        HandleDiffChunk(index, output);
      }
      else if(m_buffer[index] & 0x80){
        HandleLumaChunk(index, output);
      }
      else if(m_buffer[index] & 0x80){
        HandleLumaChunk(index, output);
      }
      else{
        return std::unexpected(LoaderError::UNKOWN_CHUNK);
      }
      // index updating is handled in the chunk handler functions
    }
  }
}
