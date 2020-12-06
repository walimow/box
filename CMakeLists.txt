cmake_minimum_required(VERSION 3.17)
project(box)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ./include
)

add_subdirectory(test)

add_executable(box main.cpp include/def.hpp include/util.hpp include/trace.hpp include/singular.hpp include/wrekurs.hpp include/detect/detect_iterable.hpp)