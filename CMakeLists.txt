cmake_minimum_required(VERSION 3.6)
project(Taskmaster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

INCLUDE_DIRECTORIES("/nfs/zfs-student-6/users/rojones/.brew/include/")
INCLUDE_DIRECTORIES("includes")
LINK_DIRECTORIES("/nfs/zfs-student-6/users/rojones/.brew/lib/")
set(SOURCE_FILES srcs/main.cpp srcs/LineEdit.cpp srcs/engine.cpp srcs/start.cpp srcs/stop.cpp srcs/restart.cpp srcs/help.cpp srcs/program.cpp srcs/initProcecces.cpp)
add_executable(Taskmaster ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Taskmaster libyaml-cpp.a)
TARGET_LINK_LIBRARIES(Taskmaster termcap.a)

