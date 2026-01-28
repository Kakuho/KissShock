#include "window.hpp"
#include "SFML/Window/Event.hpp"

#include "SFML/Window/Keyboard.hpp"
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
      if(event.type == sf::Event::KeyPressed){
        HandleKeyPress(event);
      }
    }
  }

  void Window::HandleKeyPress(sf::Event& event){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
      if(pressh_callback){
        std::println("H Key Pressed");
        pressh_callback();
        return;
      }

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
      if(pressj_callback){
        std::println("J Key Pressed");
        pressj_callback();
        return;
      }

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
      if(pressk_callback){
        std::println("K Key Pressed");
        pressk_callback();
        return;
      }

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
      if(pressl_callback){
        std::println("L Key Pressed");
        pressl_callback();
        return;
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
