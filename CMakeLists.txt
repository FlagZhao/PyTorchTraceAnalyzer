cmake_minimum_required(VERSION 3.10) 


# set the project name 
project(TorchView) 

#include_directories("./include/nlohmann")

#find nlohmann_json
#find_package(nlohmann_json 3.2.0 REQUIRED)

# add the executable 
add_executable(Convert main.cpp report.cpp ./include/util/event.h ./include/util/event.h) 