cmake_minimum_required(VERSION 3.0)
project(Huffman_compressor)

set(CMAKE_CXX_STANDARD 23)

add_executable(Huffman_compressor src/main.cpp src/Node.cpp src/Node.h src/Utils/FileOperation.cpp src/Utils/FileOperation.h)
