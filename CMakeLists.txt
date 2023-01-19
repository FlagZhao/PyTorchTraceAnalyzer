cmake_minimum_required(VERSION 3.10)

# set the project name 
project(TorchView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -no-pie")
find_package(RapidJSON REQUIRED)
# print out rapidjson include directories
message(STATUS "Rapid_INCLUDE_DIRS: ${RapidJSON_INCLUDE_DIRS}")
include_directories(${RapidJSON_INCLUDE_DIRS})

file(GLOB metrics CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/metrics/*" )
file(GLOB query CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/query/*" )
file(GLOB tree CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/tree/*" )

# add the executable 
add_executable(Convert
    ${metrics}
    ${query}
    ${tree}
    "main.cpp"
    ${Rapidjson_INCLUDE_DIRS}
)

