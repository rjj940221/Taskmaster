cmake_minimum_required(VERSION 3.6)
project(Taskmaster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

INCLUDE_DIRECTORIES("/nfs/zfs-student-6/users/rojones/.brew/include/")
LINK_DIRECTORIES("/nfs/zfs-student-6/users/rojones/.brew/lib/")
set(SOURCE_FILES src/main.cpp src/program.cpp includes/program.h)
add_executable(Taskmaster ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Taskmaster libyaml-cpp.a)