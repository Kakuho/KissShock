#pragma once

#include <cstdint>

namespace KissShock{  
  struct MovingBody;  // base class 

  class Collision{
    public:
      enum class Type{Square, Circle, Ellipse} type;
      MovingBody* movingBody;
      union{
        struct{
          std::size_t width;
          std::size_t height;
        } box;
        struct{
          std::size_t radius;
        } circle;
        struct{
          std::size_t radius;
        } ellipse;
      };

      void CalculateOrigin();
      bool CollidedWith(Collision& cf2);

    private:
      friend bool HandleSquareVsSquare(Collision& square1, Collision& square2);
      friend bool HandleSquareVsCircle(Collision& square, Collision& circle);
      friend bool HandleSquareVsEllipse(Collision& square, Collision& ellipse);
      friend bool HandleCircleVsCircle(Collision& circle1, Collision& circle2);
      friend bool HandleCircleVsEllipse(Collision& circle, Collision& ellipse);
      friend bool HandleEllipseVsEllipse(Collision& ellipse1, Collision& ellipse2);
  };
}
