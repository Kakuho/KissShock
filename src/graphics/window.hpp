#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <print>
#include <functional>

#include "SFML/Window/Event.hpp"
#include "config.hpp"

// uses sfml as the window api, maybe later i'll switch out to sdl if it turns out sfml is not multiplatform
//
// window to a 320x200 screen for the og experience

namespace KissShock{
  class FrameBuffer;

  class Window{
    static constexpr std::size_t HEIGHT = Config::WINDOW_HEIGHT;
    static constexpr std::size_t WIDTH = Config::WINDOW_WIDTH;

    public:
      Window();

      constexpr std::size_t Height() const{ return HEIGHT;}
      constexpr std::size_t Width() const{ return WIDTH;}

      void HandleEvents();
      void HandleMouseMoved(sf::Event& event);
      void HandleKeyPress(sf::Event& event);

      void SetFrameBuffer(FrameBuffer& fb);
      void SwapFrameBuffer(FrameBuffer* fb);

      void UpdateTexture();

      void Draw();

      bool IsOpen(){return m_window.isOpen();}

      void SetPressHCallback(std::function<void(void)> f){ pressh_callback = f; 
        pressh_callback(); pressh_callback(); pressh_callback(); pressh_callback();}
      void SetPressJCallback(std::function<void(void)> f){ pressj_callback = f;}
      void SetPressKCallback(std::function<void(void)> f){ pressk_callback = f;}
      void SetPressLCallback(std::function<void(void)> f){ pressl_callback = f;}

    private:
      sf::RenderWindow m_window;
      sf::View m_view;
      sf::Texture m_fbTexture;
      sf::Sprite m_fbSprite;
      FrameBuffer* m_frameBuffer;

      std::function<void(void)> pressh_callback;
      std::function<void(void)> pressj_callback;
      std::function<void(void)> pressk_callback;
      std::function<void(void)> pressl_callback;
  };
}
