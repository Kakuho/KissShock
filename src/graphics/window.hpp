#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <print>

// uses sfml as the window api, maybe later i'll switch out to sdl if it turns out sfml is not multiplatform
//
// window to a 320x200 screen for the og experience

namespace KissShock{
  class FrameBuffer;

  class Window{
    static constexpr std::size_t HEIGHT = 320;
    static constexpr std::size_t WIDTH = 200;

    public:
      Window();

      void HandleEvents();

      void SetFrameBuffer(FrameBuffer& fb);
      void SwapFrameBuffer(FrameBuffer* fb);

      void UpdateTexture();

      void Draw();

      bool IsOpen(){return m_window.isOpen();}

    private:
      sf::RenderWindow m_window;
      sf::View m_view;
      sf::Texture m_fbTexture;
      sf::Sprite m_fbSprite;
      FrameBuffer* m_frameBuffer;
  };
}
