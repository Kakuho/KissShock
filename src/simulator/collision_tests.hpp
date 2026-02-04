#pragma once

// Type CollisionTestTable is a class which represents an interface to the collision tests.
// It is this type which should be queried using the multiple subscript operator in order
// to use collision detection tests

#include <cstdint>
#include <array>
#include <functional>
#include <stdexcept>

#include "collision.hpp"

namespace KissShock{  

  class CollisionTestTable{
    using TestHandler = bool(Collision&, Collision&);
    using TestWrapper = std::function<TestHandler>;
    public:
      static const CollisionTestTable& Get(){ static CollisionTestTable tbl; return tbl;}

      TestHandler& operator[](Collision& coll1, Collision& coll2) const;

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
  };
}
