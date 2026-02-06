#include "doctest.h"  

#include "simulator/body.hpp"
#include "simulator/collision.hpp"
#include "simulator/cr_table.hpp"
#include "simulator/collision_tests.hpp"

#include "test_body.hpp"

using namespace KissShock;

TEST_CASE("Registration: CR_Table correctly registers a body"){
  CRTable colresTable;
  colresTable.Register<TestBody>();
  CHECK(TestBody::Id == 0);
}
