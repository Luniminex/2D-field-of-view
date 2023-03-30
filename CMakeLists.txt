cmake_minimum_required(VERSION 3.24)
project(LightingExample)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -lSDL2_ttf -lSDL2_image")

find_package(SDL2 REQUIRED SDL2)

add_executable(LightingExample main.cpp Game.cpp Game.h Handle.cpp Handle.h TextureWrap.cpp TextureWrap.h Entity.cpp Entity.h Box.cpp Box.h Circle.cpp Circle.h Circle.h Spotlight.cpp Spotlight.h Fieldlight.cpp Fieldlight.h Wall.cpp Wall.h)

target_link_libraries(LightingExample PRIVATE SDL2)
