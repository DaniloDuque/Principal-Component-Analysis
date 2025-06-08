cmake_minimum_required(VERSION 3.16)
project(SVD_Image_Compressor)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(src)

add_executable(SVD_Image_Compressor main.cpp ${SOURCES})
