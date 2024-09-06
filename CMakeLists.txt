cmake_minimum_required(VERSION 3.0)
project(elementary)
include_directories(./src/includes/)
set(CMAKE_C_COMPILER /usr/bin/gcc)

set(Sources
  ./src/main.c)

add_executable(${PROJECT_NAME} ${Sources})
