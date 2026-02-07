#include "doctest.h"  

#include <print>

#include "simulator/body.hpp"
#include "simulator/collision.hpp"
#include "simulator/cr_table.hpp"
#include "simulator/collision_tests.hpp"

#include "test_body.hpp"

using namespace KissShock;

TEST_CASE("Registration: CR_Table correctly registers a body"){
  CRTable colresTable;
  colresTable.Register<TestBody>();
  colresTable.Register<TestBody1>();
  colresTable.Register<TestBody2>();
  CHECK(TestBody::Id == 0);
  CHECK(TestBody1::Id == 1);
  CHECK(TestBody2::Id == 2);
}

TEST_CASE("Registration: CR_Table correctly registers a collision resolution function"){
  CRTable colresTable;
  colresTable.Register<TestBody>();
  colresTable.Register<TestBody1>();
  colresTable.Register<TestBody2>();
  CHECK(TestBody::Id == 0);
  CHECK(TestBody1::Id == 1);
  CHECK(TestBody2::Id == 2);
  colresTable.RegisterCollisionHandler(TestBody::Id, TestBody1::Id, [](Body& src){
      src.Pos().x = 200;
    }
  );

  // now we perform simulation
  TestBody b1{Vec2<int>{0, 0}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};
  TestBody1 b2{Vec2<int>{99, 99}, Vec2<int>{0, 0}, Collision::Type::Square, 100, 100};

  if(b1.CollidedWith(b2)){
    auto handler = colresTable.GetHandler(b1.GetId(), b2.GetId());
    if(handler){
      handler.value()(b1);
    }
  }

  CHECK(b1.GetPos().x == 200);
}

TEST_CASE("Registration: CRTable querying for custom resolution function"){
  CRTable colresTable;
  colresTable.Register<TestBody>();
  colresTable.Register<TestBody1>();
  colresTable.Register<TestBody2>();
  CHECK(TestBody::Id == 0);
  CHECK(TestBody1::Id == 1);
  CHECK(TestBody2::Id == 2);

  colresTable.RegisterCollisionHandler(TestBody::Id, TestBody1::Id, [](Body& src){
      src.Pos().x = 200;
    }
  );

  CHECK(colresTable.HasCustomResolution(TestBody::Id) == true);
  CHECK(colresTable.HasCustomResolution(TestBody1::Id) == false);
  CHECK(colresTable.HasCustomResolution(TestBody2::Id) == false);
}
