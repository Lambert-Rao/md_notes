cmake_minimum_required(VERSION 3.25)
project(minist)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(minist main.cpp)
target_link_libraries(minist ${OpenCV_LIBS} )
