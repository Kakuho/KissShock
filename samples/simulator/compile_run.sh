SRC_DIR="./../../src"

CXXSRC="
  ${SRC_DIR}/graphics/loaders/qoi_loader.cpp
  ${SRC_DIR}/graphics/framebuffer.cpp
  ${SRC_DIR}/graphics/renderer.cpp
  ${SRC_DIR}/graphics/window.cpp
  ${SRC_DIR}/graphics/bitmap.cpp

  ${SRC_DIR}/simulator/collision.cpp
  ${SRC_DIR}/simulator/collision_tests.cpp
  ${SRC_DIR}/simulator/cr_table.cpp
  ${SRC_DIR}/simulator/simulator.cpp
"

rm ./main

g++ main.cpp -std=c++23 -g -o main  \
     -I${SRC_DIR} \
     ${CXXSRC} \
     -lsfml-graphics -lsfml-window -lsfml-system \
    
./main
