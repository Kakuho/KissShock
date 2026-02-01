#pragma once

// Simulates the movement of bodies

#include <cstdint>

#include "util.hpp"

// you can define a bunch of integrator policies, that can then be plugged into 
struct Integrator{
  static void Integrate2D(KissShock::Vec2<int>& pos, KissShock::Vec2<int>& vel){
    pos.x = pos.x + vel.x;
    pos.y = pos.y + vel.y;
  }
};

namespace KissShock{
  // our physics engine, it will handle the simulation of movement for registered bodies, collision detection and 
  // collision resolution

  struct CollisionFrame{
    enum class Type{Square, Circle, Ellipse} type;
    union{
      struct{
        std::size_t width;
        std::size_t height;
      } box;
      struct{
        std::size_t radius;
      } circle;
      struct{
        std::size_t radius;
      } ellipse;
    };
  };

  struct HasCollided{

  };

  class MovingBody{
    public:
      virtual void Simulate() = 0;
      virtual void OnCollision(MovingBody& body) = 0;
      CollisionFrame& CFrame(){return m_collframe;}
    private:
      CollisionFrame m_collframe;
  };

  template<typename Integrator = ::Integrator>
  class NewtonianBody2d: public MovingBody{
    public:
      virtual void Simulate() override { Integrator::Integrate2D(m_pos, m_vel); }
    private:
      Vec2<int> m_pos;
      Vec2<int> m_vel;
  };

  class NewtonianBody3d: public MovingBody{

  };

  class Simulator{

  };
}

namespace MeroPong{
  class CustomBody2d: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }
    private:
      Vec2Type m_pos;
      Vec2Type m_vel;
  };

  class Wall: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }
    private:
      Vec2Type m_pos;
      Vec2Type m_vel;
  };

  class Paddle: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }

      virtual void OnCollision(MovingBody& body) override{
        // the thing is, the ball requires knowing what it'll collied with
      }
    private:
      Vec2Type m_pos;
      Vec2Type m_vel;
  };

  class Ball: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }


      virtual void OnCollision(MovingBody& body) override{
        if(body.CFrame().type == KissShock::CollisionFrame::Type::Square){

        }
      }
    private:
      Vec2Type m_pos;
      Vec2Type m_vel;
  };
}
