#include "doctest.h"  

#include "simulator/body.hpp"
#include "simulator/collision.hpp"
#include "simulator/collision_tests.hpp"

using namespace KissShock;

class TestBody: public KissShock::Body{
  public:
    TestBody(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
      Body{topleft, initialVel, coltype, width, height}
    {

    }

    virtual void Simulate(){/* empty simulation function*/ } 

    void SetPos(KissShock::Vec2<int> pos){
      m_pos = pos;
    }

  private:
};

TEST_CASE("Collision: Tests if collision detection between squares work 1"){
  TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
  TestBody b2{Vec2<int>{50, 50}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
  CHECK(b1.CollidedWith(b2) == true);
  CHECK(b2.CollidedWith(b1) == true);
}

TEST_CASE("Collision: Tests if collision detection between squares work 2"){
  TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
  TestBody b2{Vec2<int>{75, 75}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
  CHECK(b1.CollidedWith(b2) == true);
  CHECK(b2.CollidedWith(b1) == true);
}

TEST_CASE("Collision: Tests if collision detection between squares work (x axis oob)"){
  SUBCASE("y is within bounds"){
    TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{100, 99}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
  SUBCASE("y is out of bounds"){
    TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{100, 100}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
}

TEST_CASE("Collision: Tests if collision detection between squares work (x within bounds)"){
  SUBCASE("y is within bounds"){
    TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{99, 99}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == true);
    CHECK(b2.CollidedWith(b1) == true);
  }
  SUBCASE("y is out of bounds"){
    TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{99, 120}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
}

TEST_CASE("Collision: Tests if collision detection between squares work (y oob)"){
  SUBCASE("x is within bounds"){
    TestBody b1{Vec2<int>{100, 100}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{199, 200}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
  SUBCASE("x is out of bounds"){
    TestBody b1{Vec2<int>{100, 100}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{300, 200}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
}

TEST_CASE("Collision: Tests if collision detection between squares work (y within bounds)"){
  SUBCASE("x is within bounds"){
    TestBody b1{Vec2<int>{100, 100}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{199, 199}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == true);
    CHECK(b2.CollidedWith(b1) == true);
  }
  SUBCASE("x is out of bounds"){
    TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    TestBody b2{Vec2<int>{120, 99}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
    CHECK(b1.CollidedWith(b2) == false);
    CHECK(b2.CollidedWith(b1) == false);
  }
}
