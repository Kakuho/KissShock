#include "collision_tests.hpp"
#include "body.hpp"
#include <stdexcept>

namespace KissShock{
  auto CollisionTestTable::operator[](Collision& col1, Collision& col2) const -> TestHandler&{
    using enum Collision::Type;
    switch(col1.ShapeType()){
      case Square:
        return LhsSquare(col1, col2);
      case Circle:
        return LhsCircle(col1, col2);
      case Ellipse:
        return LhsEllipse(col1, col2);
    }
  }

  // decoding functions

  auto CollisionTestTable::LhsSquare(Collision& lhs, Collision& rhs) const -> TestHandler&{
    switch(rhs.ShapeType()){
      using enum Collision::Type;
      case Square:
        return TestSquareVsSquare;
      default:
        throw std::runtime_error{"CollisionTestTable::LhsSquare(...), rhs not implemented"}; 
    }
  }

  auto CollisionTestTable::LhsCircle(Collision& lhs, Collision& rhs) const -> TestHandler&{
    throw std::runtime_error{"CollisionTestTable::LhsCircle(...) is not implemented"}; 
  }

  auto CollisionTestTable::LhsEllipse(Collision& lhs, Collision& rhs) const -> TestHandler&{
    throw std::runtime_error{"CollisionTestTable::LhsEllipse(...) is not implemented"}; 
  }

  // collision tests proper
  
  bool CollisionTestTable::TestSquareVsSquare(Collision& square1, Collision& square2){
    // body.m_pos gives the top left corner, 
    // so the collision geometry of the body is (m_pos.x, m_pos.y), (m_pos.x + width, m_pos.y + height)
    auto* body1 = square1.GetBody();
    auto* body2 = square2.GetBody();
    // test along the x axis
    if(body1->GetPos().x + body1->Width() < body2->GetPos().x) return false;
    if(body2->GetPos().x + body2->Width() < body1->GetPos().x) return false;
    // test along the y axis
    if(body1->GetPos().y + body1->Width() < body2->GetPos().y) return false;
    if(body2->GetPos().y + body2->Width() < body1->GetPos().y) return false;
    return true;
  }
}
