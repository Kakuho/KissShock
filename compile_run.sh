
CXXSRC="
  src/graphics/loaders/qoi_loader.cpp
  src/graphics/framebuffer.cpp
  src/graphics/renderer.cpp
  src/graphics/window.cpp
  src/graphics/bitmap.cpp
"

rm ./main


g++ src/main.cpp -std=c++23 -g -o main  \
     -Isrc \
     ${CXXSRC} \
     -lsfml-graphics -lsfml-window -lsfml-system \
    
./main
