#pragma once

// The base class which entities must derive in order to be included within the world simulation

#include <cstdint>

#include "util.hpp"
#include "collision.hpp"

namespace KissShock{
  class Body{
    public:
      virtual void Simulate() = 0;

      virtual void OnCollision(Body& body) = 0;

      bool CollidedWith(Body& body){
        return m_collision.CollidedWith(body.m_collision);
      }

      Collision& CFrame(){return m_collision;}
      const Vec2<int>& GetPos() const { return m_pos;}
      std::size_t Height() const { return m_height;}
      std::size_t Width() const { return m_width;}

      const void CalculateCenter() { 
        m_center = Vec2<int>(m_height/2 + m_pos.x, m_width/2 + m_pos.y);
      }

    protected:
      Collision m_collision;
      Vec2<int> m_pos;
      Vec2<int> m_center;
      Vec2<int> m_vel;
      std::size_t m_width;
      std::size_t m_height;
  };
}
