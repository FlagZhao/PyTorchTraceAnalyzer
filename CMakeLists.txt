cmake_minimum_required(VERSION 3.10)

# set the project name
project(TorchView)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -no-pie")
find_package(RapidJSON REQUIRED)

# print out rapidjson include directories
message(STATUS "Rapid_INCLUDE_DIRS: ${RapidJSON_INCLUDE_DIRS}")
include_directories(${RapidJSON_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# file(GLOB header_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/include/*")
file(GLOB src_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*")

# add the library
add_library(Convert SHARED
    # ${header_files}
    ${src_files}
    ${Rapidjson_INCLUDE_DIRS}
    # "test.cpp"
)
