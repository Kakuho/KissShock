#pragma once

//  coordinate transformation functions
//
//  first you have to define your screen space and your world space...

#include <cstdint>

#include "util.hpp"

namespace KissShock{
  constexpr Vec2<std::size_t> WorldToScreen(Vec2<int> worldCoords){
    // for now we just assume we add 20 to the world coordinates lmao...
    return Vec2<std::size_t>(worldCoords.x + 20, worldCoords.y - 20);
  }

  constexpr Vec2<int> ScreenToWorld(Vec2<std::size_t> worldCoords){
    // see WorldToScreen
    return Vec2<int>(worldCoords.x - 20, worldCoords.y + 20);
  }
}
