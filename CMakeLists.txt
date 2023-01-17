cmake_minimum_required(VERSION 3.10)

# set the project name 
project(TorchView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -no-pie")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -no-pie")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg -no-pie")

include_directories(include)

# add the executable 
add_executable(Convert
    "metrics/flops.h"
    "metrics/flops.cpp"
    "metrics/metrics.h"
    "metrics/metrics.cpp"
    "query/query.h"
    "query/query.cpp"
    "tree/event.h"
    "tree/event.cpp"
    "tree/tree.h"
    "tree/tree.cpp"
    "main.cpp"
)
