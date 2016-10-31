cmake_minimum_required(VERSION 3.6)
project(Sparse_Phase_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES array.h sparse.cpp ArrayMatrix.h ArrayMatrix.cpp array.cpp ArgumentManager.h linkedlist.cpp linkedlist.h MatrixElement.h LinkedListMatrix.cpp LinkedListMatrix.h MatrixElement.cpp arraysort.h arraysearch.h)
add_executable(Sparse_Phase_2 ${SOURCE_FILES})