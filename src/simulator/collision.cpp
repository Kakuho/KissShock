#include "collision.hpp"
#include "collision_tests.hpp"

namespace KissShock{
  bool Collision::CollidedWith(Collision& cf2){
    auto collHandler = m_handlers[*this, cf2];
    return collHandler(*this, cf2);
  }
}
