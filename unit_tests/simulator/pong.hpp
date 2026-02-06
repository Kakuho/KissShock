#pragma once

#include "simulator/body.hpp"

using namespace KissShock;

namespace TestUtil{
  class PongBall: public KissShock::Body{
    public:
      PongBall(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
        Body{topleft, initialVel, coltype, width, height}
      {

      }

      virtual void Simulate() override{
        // simple constant velocity
        m_pos.x += m_vel.x;
        m_pos.y += m_vel.y;
      } 

      void SetPos(KissShock::Vec2<int> pos){
        m_pos = pos;
      }

      static void SetId(std::size_t val){ Id = val;}
      virtual std::size_t EntityId() const override{ return Id;}
      std::size_t GetId(){ return Id;}

      static std::size_t Id;
  };

  std::size_t PongBall::Id = 0;

  class PongWall: public KissShock::Body{
    public:
      PongWall(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
        Body{topleft, initialVel, coltype, width, height}
      {

      }

      virtual void Simulate() override{/* static */} 

      void SetPos(KissShock::Vec2<int> pos){
        m_pos = pos;
      }

      static void SetId(std::size_t val){ Id = val;}
      virtual std::size_t EntityId() const override{ return Id;}
      std::size_t GetId(){ return Id;}

      static std::size_t Id;
  };

  std::size_t PongWall::Id = 0;

  constexpr void PongBallOnPongWall(KissShock::Body& ball, KissShock::Body& wall){
    ball.Vel().x = -ball.Vel().x;
  }

  constexpr void PongWallOnPongBall(KissShock::Body& ball, KissShock::Body& wall){
    // the wall does nothing
  }

}
