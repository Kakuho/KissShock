#include <print>

#include "simulator/collision.hpp"
#include "simulator/simulator.hpp"
#include "simulator/cr_table.hpp"
#include "simulator/collision_tests.hpp"

#include "graphics/config.hpp"
#include "graphics/window.hpp"
#include "graphics/framebuffer.hpp"

#include "pong.hpp"

int main(){
  using namespace KissShock;
  // setting up the entities and collision resolution functions
  Simulator simul;

  simul.CollResTable().Register<Sample::PongBall>();
  simul.CollResTable().Register<Sample::PongWall>();

  Sample::PongBall ball{Vec2{0, 0}, Vec2{1, 0}, Collision::Type::Square, 2, 2};
  Sample::PongWall rightWall{Vec2{10, 0}, Vec2{0, 0}, Collision::Type::Square, 2, 10};
  Sample::PongWall leftWall{Vec2{-10, 0}, Vec2{0, 0}, Collision::Type::Square, 2, 10};

  simul.AddBody(ball);
  simul.AddBody(rightWall);
  simul.AddBody(leftWall);

  simul.CollResTable().RegisterCollisionHandler(Sample::PongBall::Id, Sample::PongWall::Id, Sample::PongBallOnPongWall);

  // setting up the renderer

  KissShock::FrameBuffer fb;
  // set up the first frame buffer
  fb.FillPixels(KissShock::Pixel{0xF2, 0x9E, 0xC8, 0xFF});
  KissShock::Window window;
  window.SetFrameBuffer(fb);
  while(window.IsOpen()){
    fb.Clear();
    simul.Tick();
    //std::println("Ball: ({}, {})", ball.Pos().x, ball.Pos().y);
    window.HandleEvents();
    fb.DrawEntities(simul.GetBodies());
    window.Draw();
  }
}
