rm ./main


g++ src/main.cpp -std=c++23 -o main  \
     -lsfml-graphics -lsfml-window -lsfml-system \
    
./main
