cmake_minimum_required(VERSION 3.3)
project(a2___collision_detection)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Shape.cpp Shape.h Circle.cpp Circle.h Square.cpp Square.h Visitor.cpp Visitor.h CollisionVisitor.cpp CollisionVisitor.h Game.cpp Game.h Vector3D.cpp Vector3D.h)
add_executable(a2___collision_detection ${SOURCE_FILES})