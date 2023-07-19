# CMake minimum version
cmake_minimum_required(VERSION 3.15)

# Project name
project(prototest)


# Find Protobuf
find_package(protobuf CONFIG REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Proto file
set(PROTO_FILES example.proto)

# Source file
set(SOURCE_FILES prototest.cpp)

# Add executable
add_executable(prototest ${SOURCE_FILES} ${PROTO_FILES})

# Link Protobuf
target_link_libraries(prototest protobuf::libprotobuf)

# Generate Protobuf code
protobuf_generate(TARGET prototest LANGUAGE cpp)
