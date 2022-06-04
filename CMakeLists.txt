cmake_minimum_required(VERSION 3.2)

Project(fbtest)

ADD_SUBDIRECTORY(fblib)

FILE(GLOB SOURCE *.cpp)
configure_file(obj/boggie/body.obj ${CMAKE_BINARY_DIR} COPYONLY) 

ADD_EXECUTABLE(fbtest ${SOURCE})

TARGET_LINK_LIBRARIES(fbtest fblib)
