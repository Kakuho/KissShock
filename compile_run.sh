
CXXSRC="
  src/graphics/loaders/qoi_loader.cpp
"

rm ./main


g++ src/main.cpp -std=c++23 -g -o main  \
     ${CXXSRC} \
     -lsfml-graphics -lsfml-window -lsfml-system \
    
./main
