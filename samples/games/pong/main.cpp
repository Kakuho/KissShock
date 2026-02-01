#include <cstdint>
#include <print>
#include <vector>

// implementation of pong, to exercise the engine as a whole

// Physics specific 

struct Vec2{
  int x;
  int y;
  friend Vec2 operator-(Vec2 vec2){ return Vec2{-vec2.x, -vec2.y};}
};

struct Vec3{
  std::uint8_t x;
  std::uint8_t y;
  std::uint8_t z;
};

template<typename T>
concept PObject = requires(T t){
  t.CollisionResponse;
};

class NewtonianBox3D{
  public:
    virtual void Step(float dt);
    virtual void DoCollisionResponse();

  private:
    Vec3 pos;
    Vec3 forceAccum;
    std::size_t width;
    std::size_t height;
    std::size_t depth;
};

class NewtonianBox2D{
  // simulates a newtonian box
  public:
    virtual void Step(float dt);
    virtual bool HasCollided(const NewtonianBox2D& box) const; // needs to know if it has collided with other entities
    virtual void DoCollisionResponse();

  protected:
    Vec2 pos;
    Vec2 vel;
    Vec2 forceAccum;
    std::size_t width;
    std::size_t height;
};

// Engines

class PEngine2D{
  void Step(float dt){
    for(auto& e : entities){
      e.Step(dt);
    }
  }
  std::vector<NewtonianBox2D> entities;
};

// Game Specific

class Wall: public NewtonianBox2D{

};

class Ball: public NewtonianBox2D{
  virtual HasCollided() const override{

  }

  bool CollidedWithWall(){

  }

  virtual void DoCollisionResponse() override{
    vel = -vel;
  }
};

int main(){

}
