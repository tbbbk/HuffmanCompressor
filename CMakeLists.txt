cmake_minimum_required(VERSION 3.0)
project(Huffman_compressor)

set(CMAKE_CXX_STANDARD 23)

add_executable(Huffman_compressor src/main.cpp src/Utils/Node.h src/Utils/FileOperation.h src/Utils/DataProcess.cpp src/Utils/Node.cpp src/Utils/FileOperation.cpp)
