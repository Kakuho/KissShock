#pragma once

// Simulates the movement of bodies
// our world simulation manager, it will handle the simulation of movement for registered bodies, collision detection and 
// collision resolution

#include <print>
#include <cstdint>
#include <list>

#include "util.hpp"
#include "body.hpp"

// you can define a bunch of integrator policies, that can then be plugged into 
struct Integrator{
  static void Integrate2D(KissShock::Vec2<int>& pos, KissShock::Vec2<int>& vel){
    pos.x = pos.x + vel.x;
    pos.y = pos.y + vel.y;
  }
};

namespace KissShock{

  struct CollisionPair{
    // what if pointer invalidation from vector?
    Body* body1;
    Body* body2;
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
  class Wall: public KissShock::Body{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      virtual void Simulate() override;
      virtual void OnCollision(Body& body);
  };

  class Paddle: public KissShock::Body{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      static constexpr std::size_t PADDLE_CID = 230;
      virtual void Simulate() override;
      virtual void OnCollision(Body& body) override{};
  };

  class Ball: public KissShock::Body{
    using Vec2Type = KissShock::Vec2<int>;
    public:
      static constexpr std::size_t BALL_CID = 100;
      virtual void Simulate() override;
      virtual void OnCollision(Body& body) override;
  };

}
