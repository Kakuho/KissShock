#pragma once

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

  bool HandleSquareVsSquare(Collision& square1, Collision& square2);
  bool HandleSquareVsCircle(Collision& square, Collision& circle);
  bool HandleSquareVsEllipse(Collision& square, Collision& ellipse);
  bool HandleCircleVsCircle(Collision& circle1, Collision& circle2);
  bool HandleCircleVsEllipse(Collision& circle, Collision& ellipse);
  bool HandleEllipseVsEllipse(Collision& ellipse1, Collision& ellipse2);

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
