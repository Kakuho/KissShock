#include "collision.hpp"
#include "collision_tests.hpp"
#include "body.hpp"

namespace KissShock{
  Collision::Collision(Body& body, Type type, const CollisionTestTable& table): 
    m_type{type},
    m_body{&body},
    m_handlers{table}
  {
    switch(m_type){
      case Type::Square:
        InitSquare();
        break;
      case Type::Ellipse:
        InitEllipse();
        break;
      case Type::Circle:
        InitCircle();
        break;
    }
  }

  void Collision::InitSquare(){
    square.width = m_body->Width();
    square.height = m_body->Height();
  }

  void Collision::InitCircle(){
    throw std::runtime_error{"Collision::InitCircle() NOT IMPLEMENTED"};
  }

  void Collision::InitEllipse(){
    throw std::runtime_error{"Collision::InitEllipse() NOT IMPLEMENTED"};
  }

  bool Collision::CollidedWith(Collision& cf2){
    auto collHandler = m_handlers[*this, cf2];
    return collHandler(*this, cf2);
  }
}
