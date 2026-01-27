cmake_minimum_required(VERSION 3.1...3.29)

project(KissShock VERSION 1.0 
                    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CXX_SRCS 
    src/main.cpp
)

add_executable(main ${CXX_SRCS})
target_link_libraries(main PRIVATE sfml-graphics)
