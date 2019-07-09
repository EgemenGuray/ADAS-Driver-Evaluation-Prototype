cmake_minimum_required(VERSION 3.10)
project(vehicleEval)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(vehicleEval
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/vehicleEval
        cmake-build-debug/vehicleEval.cbp
        CMakeLists.txt
        deqll.c
        deqll.h
        main.c
        oracle.c
        oracle.h)
