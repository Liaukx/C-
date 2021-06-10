cmake_minimum_required(VERSION 3.19)
project(Book_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(Book_demo main.cpp Book.h schedule.h account.cpp account.h Date.h Date.cpp)