cmake_minimum_required(VERSION 3.21)
project(Task04)

set(CMAKE_CXX_STANDARD 11)

#add_executable(Task04 main.cpp)
add_executable(
        Task04
        Point.cpp
        Point.h
        Quad.cpp
        Quad.h
        Square.cpp
        Square.h
        Shape.cpp
        Shape.h
        Circle.cpp
        Circle.h
        allShapes.cpp
        allShapes.h
        MainTrain.cpp
)
