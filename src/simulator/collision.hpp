#pragma once

#include <cstdint>
#include <print>
#include <stdexcept>

#include "util.hpp"

namespace KissShock{  

  class Body;
  class CollisionTestTable;

  class Collision{
    public:
      enum class Type{Square, Circle, Ellipse};

      Collision(Body& body, Type type, const CollisionTestTable& table);

      constexpr Type ShapeType() const{ return m_type;}
      const Vec2<int>& GetCenter() const;
      const Body* GetBody(){ return m_body;}

      bool CollidedWith(Collision& cf2);

    private:
      void InitSquare();
      void InitCircle();
      void InitEllipse();

      Body* m_body;
      Type m_type;
      const CollisionTestTable& m_handlers;
      union{
        struct{
          std::size_t width;
          std::size_t height;
        } square;
        struct{
          std::size_t radius;
        } circle;
        struct{
          std::size_t radius;
        } ellipse;
      };
  };
}
