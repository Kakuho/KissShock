#include <print>
#include <cstring>
#include <stdexcept>

#include "graphics/config.hpp"
#include "graphics/window.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/loaders/qoi_loader.hpp"
#include "util.hpp"

// file to exercise functionality of FrameBuffer and Window

static constexpr std::string ASSET_PATH = "../../assets";

void SampleFrameBuffer(){
  using namespace KissShock;
  FrameBuffer framebuffer;;
  // set up the first frame buffer
  framebuffer.FillPixels(Pixel{0xF2, 0x9E, 0xC8, 0xFF});

  for(auto i = 0ul; i < 10; i++){
    framebuffer.WritePixel(Vec2{i, 0ul}, Pixel{0xFF, 0xFF, 0xFF, 0xFF});
  }

  for(auto i = 0ul; i < 20; i++){
    framebuffer.WritePixel(Vec2{0ul, i}, Pixel{0x00, 0xFF, 0x00, 0xFF});
  }

  Window window;
  window.SetFrameBuffer(framebuffer);
  while(window.IsOpen()){
    window.HandleEvents();
    window.Draw();
  }
}

void PlayEtchSketch(){
  using namespace KissShock;
  FrameBuffer framebuffer;;
  // set up the first frame buffer
  Window window;
  window.SetFrameBuffer(framebuffer);
  Vec2 pos{0ul, 0ul};

  window.SetPressHCallback([&pos](){
    if(pos.x == 0){
      pos.x = Config::WINDOW_WIDTH;
    }
    else{
      pos.x--;
    }
  });

  window.SetPressJCallback([&pos](){
    if(pos.y == 0){
      pos.y = Config::WINDOW_HEIGHT;
    }
    else{
      pos.y--;
    }
  });

  window.SetPressKCallback([&pos](){
    if(pos.y == Config::WINDOW_HEIGHT){
      pos.y = 0;
    }
    else{
      pos.y++;
    }
  });

  window.SetPressLCallback([&pos](){
    if(pos.x == Config::WINDOW_WIDTH){
      pos.x = 0;
    }
    else{
      pos.x++;
    }
  });

  std::println("pos: {}, {}", pos.x, pos.y);

  while(window.IsOpen()){
    framebuffer.Clear();
    window.HandleEvents();
    framebuffer.WritePixel(pos, Pixel{0xff, 0xff, 0xff, 0xff});
    window.Draw();
  }
}

void DrawBitmap(){
  KissShock::FrameBuffer fb;
  // set up the first frame buffer
  fb.FillPixels(KissShock::Pixel{0xF2, 0x9E, 0xC8, 0xFF});
  KissShock::QoiLoader qld{ASSET_PATH + "/mero_colours.qoi"};
  auto bitmap = qld.GenerateBitmap();
  if(bitmap){
    bitmap->PrintData();
    fb.DrawBitmap(KissShock::Vec2{100ul, 50ul}, *bitmap);
  }
  else{
    throw std::runtime_error{"Bitmap does not hold an image"};
  }
  KissShock::Window window;
  window.SetFrameBuffer(fb);
  while(window.IsOpen()){
    window.HandleEvents();
    window.Draw();
  }
}

int main(){
  DrawBitmap();
}
