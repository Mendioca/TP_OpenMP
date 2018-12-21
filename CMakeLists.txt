cmake_minimum_required(VERSION 3.0)

project(tp_OpenMP)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -DOMP_USE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -DOMP_USE")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")


set(SRC
        src/charMatrix.cpp
        src/Algorithms.cpp
        src/Timer.cpp)

set(HEADERS
        src/Algorithms.h
        src/Timer.h
        src/Utils.h)

add_executable(exec ${SRC} ${HEADERS})