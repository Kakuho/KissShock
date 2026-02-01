#include "graphics/window.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/loaders/qoi_loader.hpp"
#include "graphics/bitmap.hpp"
#include <stdexcept>

void SampleFrameBufferLines(){
  using namespace KissShock;
  FrameBuffer fb{};
  fb.DrawHorizontalLine(Vec2{4, 1}, 5, Pixel{0xFF, 0xFF, 0xFF, 0xFF});
  fb.DrawVerticalLine(Vec2{150, 41}, 10, Pixel{0x00, 0x00, 0x00, 0xFF});
  fb.DrawRectangle(Vec2{20, 60}, Vec2{60, 100}, Pixel{0x00, 0x00, 0xFF, 0xFF});
  Window window{};
  window.SetFrameBuffer(fb);
  while(true){
    window.HandleEvents();
    window.Draw();
  }
}

void FrameBufferQoi(){
  using namespace KissShock;
  QoiLoader loader{"assets/mero_head.qoi"};
  //QoiLoader loader{"assets/mero_colours.qoi"};
  auto bitmap = loader.GenerateBitmap();
  if(!bitmap){
    throw std::runtime_error{"Error: Bitmap decoding not successful"};
  }
  bitmap->DumpAsPpm("mero_head.ppm");
  FrameBuffer fb{};
  fb.DrawBitmap(Vec2{0, 0}, *bitmap);
  Window window{};
  window.SetFrameBuffer(fb);
  while(true){
    window.HandleEvents();
    window.Draw();
  }
}

void BitmapTests(){
  using namespace KissShock;
  std::vector<std::uint8_t> values{
    0xff, 0xeb, 0xf8, 0xff,
    0x60, 0x5a, 0x65, 0xff,
    0xff, 0xc5, 0xed, 0xff,
    0x7a, 0x46, 0xca, 0xff,
    0x00, 0x00, 0x00, 0x00,
    0x85, 0x73, 0xfd, 0xff,
    0xff, 0x87, 0xf0, 0xff,
    0xd9, 0xa0, 0x66, 0xff,
    0xff, 0xeb, 0xf8, 0xff
  };
  Bitmap bitmap{3, 3, std::move(values)};
  assert(bitmap.PixelAt(Vec2{0l, 0l}).red == 0xff);
  assert(bitmap.PixelAt(Vec2{0l, 0l}).green == 0xeb);
  assert(bitmap.PixelAt(Vec2{0l, 0l}).blue == 0xf8);
  assert(bitmap.PixelAt(Vec2{0l, 0l}).alpha == 0xff);

  assert(bitmap.PixelAt(Vec2{1l, 0l}).red == 0x60);
  assert(bitmap.PixelAt(Vec2{1l, 0l}).green == 0x5a);
  assert(bitmap.PixelAt(Vec2{1l, 0l}).blue == 0x65);
  assert(bitmap.PixelAt(Vec2{1l, 0l}).alpha == 0xff);

  assert(bitmap.PixelAt(Vec2{2l, 0l}).red == 0xff);
  assert(bitmap.PixelAt(Vec2{2l, 0l}).green == 0xc5);
  assert(bitmap.PixelAt(Vec2{2l, 0l}).blue == 0xed);
  assert(bitmap.PixelAt(Vec2{2l, 0l}).alpha == 0xff);

  assert(bitmap.PixelAt(Vec2{0l, 1l}).red == 0x7a);
  assert(bitmap.PixelAt(Vec2{0l, 1l}).green == 0x46);
  assert(bitmap.PixelAt(Vec2{0l, 1l}).blue == 0xca);
  assert(bitmap.PixelAt(Vec2{0l, 1l}).alpha == 0xff);
}

int main(){
  FrameBufferQoi();
}
