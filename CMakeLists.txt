cmake_minimum_required(VERSION 3.10)

# set the project name 
project(TorchView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# add the executable 
add_executable(Convert
    "include/util/event.h"
    "include/util/flops.h"
    "include/util/metrics.h"
    "include/util/tree.h"
    "event.cpp"
    "flops.cpp"
    "metrics.cpp"
    "tree.cpp"
    "main.cpp"
)
