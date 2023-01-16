cmake_minimum_required(VERSION 3.10)

# set the project name 
project(TorchView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# add the executable 
add_executable(Convert
    "metrics/flops.h"
    "metrics/flops.cpp"
    "metrics/metrics.h"
    "metrics/metrics.cpp"
    "tree/event.h"
    "tree/event.cpp"
    "tree/tree.h"
    "tree/tree.cpp"
    "main.cpp"
)
