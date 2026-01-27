#include "SFML/Config.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics/Image.hpp>
#include <print>
#include <cstring>

void HandleEvents(sf::RenderWindow& window){
  sf::Event event;
  while (window.pollEvent(event)){
    if (event.type == sf::Event::Closed){
      std::println("Exiting...");
      window.close();
    }
  }
}

void RenderPoints(){
  std::size_t h = 50;
  std::size_t w = 50;
  sf::RenderWindow window(sf::VideoMode(h, w),"Kiss Shock", sf::Style::Fullscreen);
  window.setFramerateLimit(30);

  sf::View view{sf::Vector2f(h/2.0f, w/2.0f), sf::Vector2f(h, w)};
  window.setView(view);

  constexpr std::size_t NPOINTS = 10;
  sf::VertexArray points{sf::PrimitiveType::Points, NPOINTS};

  sf::VertexArray points2D{sf::PrimitiveType::Points, 40*40};

  for(std::size_t j = 0; j < 40; j++){
    for(std::size_t i = 0; i < 40; i++){
      points2D[i + j*40].position = sf::Vector2f(0.5f*i, 0.5f*j);
      points2D[i].color = sf::Color::Magenta;
    }
  }

  /*
  for(std::size_t i = 0; i < 10; i++){
    points[i].position = sf::Vector2f(0.5f*i, 2.5f);
    points[i].color = sf::Color::Magenta;
  }
  */

  while(window.isOpen())
  {
    HandleEvents(window);
    window.clear();
    window.draw(points2D);
    window.display();
  }
}

void Sample(){
  sf::RenderWindow window(sf::VideoMode(320, 200),"Kiss Shock", sf::Style::Resize);
  window.setFramerateLimit(30);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    HandleEvents(window);
    window.clear();
    window.draw(shape);
    window.display();

  }
}



struct Framebuffer{
  Framebuffer(){
    texture.create(50, 50);
  }

  void Clear(){
    std::memset(pixels, 0, 50*50*4);
    texture.update(pixels);
    bufferSprite.setTexture(texture);
  }

  void DrawCursor(std::size_t i, sf::Color& colour){
    pixels[i] = colour.r;
    pixels[i + 1] = colour.g;
    pixels[i + 2] = colour.b;
    pixels[i + 3] = colour.a;
    texture.update(pixels);
    bufferSprite.setTexture(texture);
  }

  sf::Uint8* pixels = new sf::Uint8[50 * 50 * 4]; // * 4 because pixels have 4 components (RGBA)
  sf::Texture texture;
  sf::Sprite bufferSprite;
};

void DrawFrameBuffer(Framebuffer& fb, sf::RenderWindow& window){
  window.draw(fb.bufferSprite);
  window.display();
}

void RenderFromImage(){
  sf::RenderWindow App{sf::VideoMode(50, 50), "SFML Graphics", sf::Style::Resize};
  sf::View view1{sf::Vector2f(50/2.0f, 50/2.0f), sf::Vector2f(50, 50)};
  sf::View view2{sf::FloatRect{0,  0, 50, 50}};
  App.setView(view2);

  Framebuffer fb;
  sf::Color cursorColour = sf::Color{0xFF, 0xFF, 0xFF, 0xFF};
  bool colour_toggle = true;

	App.clear();
  std::size_t i = 0;
  while (App.isOpen())
  {
    HandleEvents(App);
    fb.Clear();
    fb.DrawCursor(i, cursorColour);
    DrawFrameBuffer(fb, App);
    i += 4;
    if(i ==50 * 50 * 4){
      if(colour_toggle){
        cursorColour = sf::Color{0xFF, 0xb6, 0xc1, 0xFF};
        colour_toggle = !colour_toggle;
      }
      else{
        cursorColour = sf::Color{0xFF, 0xFF, 0xFF, 0xFF};
        colour_toggle = !colour_toggle;
      }
      i = 0;
    }
  }
}

int main(){
  RenderFromImage();
}
