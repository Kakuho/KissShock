#include "simulator.hpp"

namespace KissShock{
  void Simulator::Tick(){
    for(auto& body: m_bodies){
      body->Simulate();
    }
    HandleCollisions();
  }

  std::list<CollisionPair> Simulator::DetectCollisions(){
    std::list<CollisionPair> collisions;
    for(auto& body1: m_bodies){
      for(auto& body2: m_bodies){
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

  // problem is that we want the engine to own all entity instances, 
  // it shouldn't fall to the user to create a body and then register them into simulator...
  void Simulator::AddBody(Body& body){
    m_bodies.push_back(&body);
  }
}
