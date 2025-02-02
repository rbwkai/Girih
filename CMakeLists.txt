cmake_minimum_required(VERSION 3.10)
project(Girih)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Girih 
  src/main.cpp
  lodepng/lodepng.cpp
  src/object/obj.cpp
  src/canvas/canvas.cpp
  src/param/parameter.cpp
)

