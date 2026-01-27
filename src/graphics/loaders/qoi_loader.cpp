#include "qoi_loader.hpp"
#include <bit>
#include <exception>
#include <fstream>

namespace KissShock{
  QoiLoader::QoiLoader(std::string_view filename)
    :
      m_pos{DATA_START},
      m_lastPixel{INITIAL_PIXEL}
  {
    std::ifstream ifst{filename.data(), std::ios_base::ate};
    std::size_t size = ifst.tellg();
    ifst.seekg(0);
    // read the data into some buffer
    char raw[size];
    ifst.readsome(raw, size);
    m_buffer = std::move(std::vector<std::uint8_t>{raw, raw+size});
    InitHeader();
  }

  void QoiLoader::SetLastPixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha){
    // created a function so that if i want to switch representation of Pixel it would be easy
    m_lastPixel = Pixel{red, blue, green, alpha};
  }

  void QoiLoader::SetLastPixel(Pixel pixel){
    // created a function so that if i want to switch representation of Pixel it would be easy
    m_lastPixel = pixel;
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
  
  std::expected<std::vector<std::uint8_t>, QoiLoader::LoaderError> QoiLoader::Decode(){
    if(m_header.header != MAGIC){
      return std::unexpected(LoaderError::MAGIC_FAILED);
    }
    std::size_t imageSize = m_header.width * m_header.height * m_header.channels;
    std::vector<std::uint8_t> output(imageSize);  // init with imageSize amount of elements
    while(!IsEndBlock(m_pos)){
      if(m_buffer[m_pos] == 0xFE){
        HandleRGBChunk(output);
      }
      else if(m_buffer[m_pos] == 0xFF){
        HandleRGBAChunk(output);
      }
      else if((m_buffer[m_pos] >> 6) == 0b11){
        HandleRunChunk(output);
      }
      else if((m_buffer[m_pos] >> 6) ==  0b00){
        HandleIndexChunk(output);
      }
      else if((m_buffer[m_pos] >> 6) == 0b01){
        HandleDiffChunk(output);
      }
      else if((m_buffer[m_pos] >> 6) == 0b10){
        HandleLumaChunk(output);
      }
      else{
        return std::unexpected(LoaderError::UNKOWN_CHUNK);
      }
      // index updating is handled in the chunk handler functions
    }
    return output;
  }

  void QoiLoader::HandleRGBChunk(std::vector<std::uint8_t>& output){ 
    std::uint8_t red = m_buffer[m_pos + 1];
    std::uint8_t blue = m_buffer[m_pos + 2];
    std::uint8_t green = m_buffer[m_pos + 3];
    output.push_back(red);
    output.push_back(blue);
    output.push_back(green);
    output.push_back(m_lastPixel.alpha);
    SetLastPixel(red, green, blue, m_lastPixel.alpha);
    m_window.Push(m_lastPixel);
    m_pos += 4;
  }

  void QoiLoader::HandleRGBAChunk(std::vector<std::uint8_t>& output){ 
    std::uint8_t red = m_buffer[m_pos + 1];
    std::uint8_t blue = m_buffer[m_pos + 2];
    std::uint8_t green = m_buffer[m_pos + 3];
    std::uint8_t alpha = m_buffer[m_pos + 4];
    output.push_back(red);
    output.push_back(blue);
    output.push_back(green);
    output.push_back(alpha);
    SetLastPixel(red, green, blue, alpha);
    m_window.Push(m_lastPixel);
    m_pos += 5;
  }

  void QoiLoader::HandleIndexChunk(std::vector<std::uint8_t>& output){ 
    std::uint8_t pindex = m_buffer[m_pos] & 0x3F;
    auto pixel = m_window.Get(m_pos);
    output.push_back(pixel.red);
    output.push_back(pixel.green);
    output.push_back(pixel.blue);
    output.push_back(pixel.alpha);
    m_lastPixel = pixel;
    m_pos += 1;
  }
}
