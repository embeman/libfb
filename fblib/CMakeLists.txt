cmake_minimum_required(VERSION 3.2)

Project(fblib)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

FILE(GLOB SOURCE *.cpp)

ADD_LIBRARY(fblib  ${SOURCE})
