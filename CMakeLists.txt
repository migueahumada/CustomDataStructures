# minimum cmake version
cmake_minimum_required(VERSION 3.31)

# name of the project, and language
project(CustomDataStructures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(HEADERS MKVector.h)

SET(SOURCE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})






