cmake_minimum_required(VERSION 3.10)

# set the project name 
project(TorchView)

include_directories(include)

# add the executable 
add_executable(Convert
    "include/util/event.h"
    "include/util/flops.h"
    "include/util/tree.h"
    "event.cpp"
    "flops.cpp"
    "tree.cpp"
    "main.cpp"
)
