
SRC_DIR="/home/ka/C++/projects/kiss_shock/branches/unit_tests/src"

CXXSRC="
  ${SRC_DIR}/simulator/collision.cpp
  ${SRC_DIR}/simulator/collision_tests.cpp
  ${SRC_DIR}/simulator/cr_table.cpp
  ${SRC_DIR}/simulator/simulator.cpp
"

TEST_DIR="
  /home/ka/C++/projects/kiss_shock/branches/unit_tests/unit_tests
"

TEST_SRC="
  ./collision.cpp
  ./resolution.cpp
  ./test_body.cpp
  ./tick.cpp
"

rm ./tests

g++ ../test_main.cpp -std=c++23 -g -o tests  \
     ${TEST_SRC} \
     -I${SRC_DIR} -I${TEST_DIR}\
     ${CXXSRC} \
    
./tests
