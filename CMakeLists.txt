cmake_minimum_required(VERSION 3.2)

Project(fbtest)

ADD_SUBDIRECTORY(fblib)

FILE(GLOB SOURCE *.cpp)

ADD_EXECUTABLE(fbtest ${SOURCE})

TARGET_LINK_LIBRARIES(fbtest fblib)
