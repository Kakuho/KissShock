#pragma once

#include <cstdint>

namespace KissShock{  

  class Body;
  class CollisionTestTable;

  class Collision{
    public:
      enum class Type{Square, Circle, Ellipse};

      Collision(const CollisionTestTable& table): m_handlers{table}{}

      constexpr Type ShapeType() const{ return m_type;}
      bool CollidedWith(Collision& cf2);

    private:
      const CollisionTestTable& m_handlers;
      Type m_type;
      Body* m_body;
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
  };
}
