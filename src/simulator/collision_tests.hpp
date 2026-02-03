#pragma once

// Type CollisionTestTable is a class which represents an interface to the collision tests.
// It is this type which should be queried using the multiple subscript operator in order
// to use collision detection tests

#include <cstdint>
#include <array>
#include <functional>

#include "collision.hpp"

namespace KissShock{  

  class CollisionTestTable{
    using TestHandler = bool(Collision&, Collision&);
    using TestWrapper = std::function<TestHandler>;
    public:
      const CollisionTestTable& Get() const{ static CollisionTestTable tbl; return tbl;}

      constexpr TestHandler& operator[](Collision& coll1, Collision& coll2) const;

    private:
      // to simplify collision test querying
      TestHandler& LhsSquare(Collision& lhs, Collision& rhs) const;
      TestHandler& LhsCircle(Collision& lhs, Collision& rhs) const;
      TestHandler& LhsEllipse(Collision& lhs, Collision& rhs) const;

      // the collision tests themselves
      static bool TestSquareVsSquare(Collision& square1, Collision& square2);
      static bool TestSquareVsCircle(Collision& square, Collision& circle);
      static bool TestSquareVsEllipse(Collision& square, Collision& ellipse);
      static bool TestCircleVsCircle(Collision& circle1, Collision& circle2);
      static bool TestCircleVsEllipse(Collision& circle, Collision& ellipse);
      static bool TestEllipseVsEllipse(Collision& ellipse1, Collision& ellipse2);

      std::array<TestWrapper, 9> m_handlers;
  };

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
