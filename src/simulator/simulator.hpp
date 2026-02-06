#pragma once

// Simulates the movement of bodies
// our world simulation manager, it will handle the simulation of movement for registered bodies, collision detection and 
// collision resolution

#include <print>
#include <cstdint>
#include <list>

#include "util.hpp"
#include "body.hpp"
#include "cr_table.hpp"

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
          body->Simulate();
        }
        HandleCollisions();
      }

      std::list<CollisionPair> DetectCollisions(){
        std::list<CollisionPair> collisions;
        for(auto& body1: bodies){
          for(auto& body2: bodies){
            // O(n^2) collision detection
            if(&body1 == &body2){
              continue;
            }
            if(body1->CollidedWith(*body2)){
              collisions.push_back(CollisionPair{body1, body2});
            }
          }
        }
        return collisions;
      }

      void HandleCollisions(){
        std::list<CollisionPair> collisions = std::move(DetectCollisions());
        for(auto collisionPair: collisions){
          auto [body1, body2] = collisionPair;
          if(m_crtable.HasCustomResolution(body1->EntityId())){
            auto handler = m_crtable.GetHandler(body1->EntityId(), body2->EntityId());
            if(handler){
              handler.value()(*body1);
            }
          }
        }
      }

    private:
      std::list<Body*> bodies;
      CRTable m_crtable;
  };
}
