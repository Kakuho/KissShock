#pragma once

// Database for sprite lookup

#include <string_view>
#include <unordered_map>
#include <string>

#include "sprite.hpp"

namespace KissShock{
  class SpriteDb{
    public:
      const Sprite* GetSprite(std::string_view name){
        // would be nice if std::expected and std::optional allows reference return types
        if(m_sprites.contains(name.data())){
          return &m_sprites[name.data()];
        }
        else{
          return nullptr;
        }
      }
    private:
      std::unordered_map<std::string, Sprite> m_sprites;  // hashmap for E(Theta(1)) lookups
  };
}
