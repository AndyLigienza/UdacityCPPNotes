cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

project(executes)

add_executable(run_execs executes/main.cpp executes/increment_and_sum.cpp executes/vect_add_one.cpp)
