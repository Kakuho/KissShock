#pragma once

// The base class which entities must derive in order to be included within the world simulation

#include <cstdint>

#include "util.hpp"
#include "collision.hpp"
#include "collision_tests.hpp"

namespace KissShock{
  class Body{
    public:
      Body(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
        m_collision{*this, coltype, CollisionTestTable::Get()},
        m_pos{topleft},
        m_vel{initialVel},
        m_width{width},
        m_height{height}
      {
        UpdateCenter();
      }

      virtual void Simulate() = 0;

      bool CollidedWith(Body& body){
        return m_collision.CollidedWith(body.m_collision);
      }

      Collision& CFrame(){return m_collision;}
      const Vec2<int>& GetPos() const { return m_pos;}
      const Vec2<int>& GetCenter() const { return m_pos;}
      std::size_t Height() const { return m_height;}
      std::size_t Width() const { return m_width;}

      constexpr std::size_t MinX() const noexcept { return m_pos.x;}
      constexpr std::size_t MaxX() const noexcept { return m_pos.x + m_width - 1;}

      constexpr std::size_t MinY() const noexcept { return m_pos.y;}
      constexpr std::size_t MaxY() const noexcept { return m_pos.y + m_height - 1;}

      const void UpdateCenter() { 
        m_center = Vec2<int>(m_height/2 + m_pos.x, m_width/2 + m_pos.y);
      }

      constexpr std::size_t EntityId() const { return m_entityId;}
      constexpr void SetEntityId(std::size_t id){ m_entityId = id;}

    protected:
      Collision m_collision;
      Vec2<int> m_pos;
      Vec2<int> m_center;
      Vec2<int> m_vel;
      std::size_t m_entityId;   // used to interface with the simulator sub systems
      std::size_t m_width;
      std::size_t m_height;
  };
}
