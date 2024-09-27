cmake_minimum_required(VERSION 3.5.0)
project(ChessClasses VERSION 0.1.0 LANGUAGES C CXX)


# target_include_directories(ChessClasses PUBLIC
#  "C:/Users/79610/Projects/ChessTPU/testing/simpleGUI"

#)
# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(ChessClasses main.cpp ChessLogic.cpp)

