#include "window.hpp"
#include "graphics/framebuffer.hpp"

namespace KissShock{
  Window::Window()
    :
      m_window{sf::VideoMode(HEIGHT, WIDTH), "KissShock Engine", sf::Style::Resize},
      m_view{sf::FloatRect{0,  0, WIDTH, HEIGHT}}
  {
    m_window.setView(m_view);
    m_fbTexture.create(WIDTH, HEIGHT);
  }

  void Window::HandleEvents(){
    sf::Event event;
    while(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        std::println("Exiting...");
        m_window.close();
      }
    }
  }

  void Window::SetFrameBuffer(FrameBuffer& fb){
    m_frameBuffer = &fb;
  }

  void Window::SwapFrameBuffer(FrameBuffer* fb){
    FrameBuffer* tmp = m_frameBuffer;
    m_frameBuffer = fb;
    fb = tmp;
  }

  void Window::UpdateTexture(){
    if(!m_frameBuffer){
      return;
    }
    m_fbTexture.update(m_frameBuffer->Get());
    m_fbSprite.setTexture(m_fbTexture);
  }

  void Window::Draw(){
    m_window.clear();
    UpdateTexture();
    m_window.draw(m_fbSprite);
    m_window.display();
  }
}
