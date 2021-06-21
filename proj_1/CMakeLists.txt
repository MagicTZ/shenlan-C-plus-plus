CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(project1)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# FIND_PACKAGE()

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)

# ADD_EXECUTABLE([文件] ${变量名})

#SUB_DIRECTORY()
