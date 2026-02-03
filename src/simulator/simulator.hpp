#pragma once

// Simulates the movement of bodies

#include <print>
#include <cstdint>
#include <list>

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

  bool CollisionSquareSquareTest(CollisionFrame& cf1, CollisionFrame& cf2){
    std::println("Square on Square Collision Test");
    return true;
  }

  struct CollisionPair{
    MovingBody& body1;
    MovingBody& body2;
  };

  class Simulator{
    // what if we use a collision handler table which allows users to define 
    // custom collision resolution handling 
    public:
      void Tick(){
        for(auto& body: bodies){
          body.Simulate();
        }

      }

      std::list<CollisionPair> DetectCollisions(){
        std::list<CollisionPair> collisions;
        for(auto& body1: bodies){
          for(auto& body2: bodies){
            // O(n^2) collision detection
            if(&body1 == &body2){
              continue;
            }
            if(body1.CollidedWith(body2)){
              collisions.push_back(CollisionPair{body1, body2});
            }
          }
        }
        return collisions;
      }

      void HandleCollisions(){

      }

      void RegisterBody(MovingBody& body){
        bodies.push_back(body);
      }

    private:
      std::list<MovingBody> bodies;
  };
}

namespace MeroPong{
  class Wall: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override { 
        // a wall does nothing, so simulation does not do anything
      }
      virtual void OnCollision(MovingBody& body){

      }
    private:
  };

  class Paddle: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      static constexpr std::size_t PADDLE_CID = 230;

      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }

      virtual void OnCollision(MovingBody& body) override{
      }
  };

  class Ball: public KissShock::MovingBody{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      static constexpr std::size_t BALL_CID = 100;
      virtual void Simulate() override { 
        // do whatever you want bruh its your own custom body
      }

      virtual void OnCollision(MovingBody& body) override{
        if(auto wall = dynamic_cast<Wall*>(&body); wall){
          m_vel.x = -m_vel.x;
        }
        else if(dynamic_cast<Paddle&>(body)){
          m_vel.x = -m_vel.x;
        }
        else if(dynamic_cast<Paddle&>(body)){
          m_vel.x = -m_vel.x;
        }
      }
  };

}
