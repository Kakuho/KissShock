#include "simulator.hpp"

namespace KissShock{
  void Simulator::Tick(){
    for(auto& body: bodies){
      body->Simulate();
    }
    HandleCollisions();
  }

  std::list<CollisionPair> Simulator::DetectCollisions(){
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

  void Simulator::HandleCollisions(){
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
}
