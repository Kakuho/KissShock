// AABB Test sample

#include <cstdint>
#include <list>
#include <print>
#include <variant>

struct Vec2{
  std::size_t x;
  std::size_t y;
};


/*
struct CollisionCircle;
struct CollisionRectangle;

struct Collision{
  virtual bool CollidedWith(Collision& collision){ return collision.CollidedWith(*this);}
  virtual bool CollidedWith(CollisionCircle& collision) = 0;
  virtual bool CollidedWith(CollisionRectangle& collision) = 0;
};

struct CollisionCircle: Collision{
  Vec2 origins;
  std::size_t radius;

  virtual bool CollidedWith(CollisionCircle& circle) override{
    std::println("Circle Collided With Circle?");
    return true;
  };

  virtual bool CollidedWith(CollisionRectangle& rectangle) override{
    std::println("Circle Collided With Rectangle?");
    return true;
  };

};

struct CollisionRectangle: Collision{
  Vec2 pos;

  std::size_t width;
  std::size_t height;

  virtual bool CollidedWith(CollisionCircle& circle) override{
    std::println("Rectangle Collided With Circle?");
    return true;
  };

  virtual bool CollidedWith(CollisionRectangle& rectangle) override{
    std::println("Rectangle Collided With Rectangle?");
    return true;
  };
};
*/

struct CollisionSquare{
  Vec2 pos;
  std::size_t length;
};

struct CollisionRectangle{
  Vec2 pos;
  std::size_t length;
  std::size_t width;
};

struct Body;

struct Collision{
  Collision(CollisionSquare cs): shape{cs}{}
  enum class Type{Square, Rectangle, Circle};
  std::variant<CollisionSquare, CollisionRectangle> shape;
  Body* body;
};

struct Body{
  Vec2 pos;
  Collision collision;
};

struct CollisionDetector{
  using CollisionPairs = std::pair<Collision*, Collision*>;
  std::list<Collision> collisions;

  std::list<CollisionPairs> Detect(){
    std::list<CollisionPairs> collisionPairs;
    // detect the collisions
    for(auto& e1: collisions){
      for(auto& e2: collisions){
        if(e1.HasCollidedWith(e2)){
          collisionPairs.push_back(std::pair{&e1, &e2});
        }
      }
    }
    return collisionPairs;
  }
};

int main(){
  std::list<Collision> collisions;
  collisions.push_back(Collision{CollisionSquare{}});
}
