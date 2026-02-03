#pragma once

// Type CollisionTestTable is a class which represents an interface to the collision tests.
// It is this type which should be queried using the multiple subscript operator in order
// to use collision detection tests

#include <cstdint>

#include "collision.hpp"

namespace KissShock{  

  class CollisionTestTable{
    using TestHandler = bool(Collision&, Collision&);
    public:
      constexpr TestHandler& operator[](Collision& coll1, Collision& coll2) const;

    private:
      TestHandler& LhsSquare(Collision& lhs, Collision& rhs) const;
      TestHandler& LhsCircle(Collision& lhs, Collision& rhs) const;
      TestHandler& LhsEllipse(Collision& lhs, Collision& rhs) const;
  };

  bool TestSquareVsSquare(Collision& square1, Collision& square2);
  bool TestSquareVsCircle(Collision& square, Collision& circle);
  bool TestSquareVsEllipse(Collision& square, Collision& ellipse);
  bool TestCircleVsCircle(Collision& circle1, Collision& circle2);
  bool TestCircleVsEllipse(Collision& circle, Collision& ellipse);
  bool TestEllipseVsEllipse(Collision& ellipse1, Collision& ellipse2);

  constexpr auto CollisionTestTable::operator[](Collision& col1, Collision& col2) const -> TestHandler&{
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
}
