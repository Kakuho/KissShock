#include "doctest.h"  

#include <print>

#include "simulator/collision.hpp"
#include "simulator/simulator.hpp"
#include "simulator/cr_table.hpp"
#include "simulator/collision_tests.hpp"

#include "test_body.hpp"
#include "pong.hpp"

using namespace KissShock;

TEST_CASE("Tick: Simulator Tick should update the position of its entities"){
  Simulator simul;

  simul.CollResTable().Register<TestUtil::PongBall>();
  simul.CollResTable().Register<TestUtil::PongWall>();

  TestUtil::PongBall ball{Vec2{0, 0}, Vec2{1, 0}, Collision::Type::Square, 10, 10};
  TestUtil::PongWall rightWall{Vec2{10, 0}, Vec2{0, 0}, Collision::Type::Square, 10, 1000};
  TestUtil::PongWall leftWall{Vec2{-10, 0}, Vec2{0, 0}, Collision::Type::Square, 10, 1000};

  simul.AddBody(ball);
  simul.AddBody(rightWall);
  simul.AddBody(leftWall);
  
  simul.Tick();
  CHECK(ball.Pos().x == 1);
}
