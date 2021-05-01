cmake_minimum_required(VERSION 3.9)
project(Antocoon)


set(CMAKE_CXX_STANDARD 11)
add_executable(Antocoon
        cmake-build-debug/Antocoon.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/log.dat
        cmake-build-debug/Makefile
        cmake-build-debug/users.dat
        CMakeLists.txt
        main.cpp
        social.cpp
        social.h menu.h menu.cpp
        tree.cpp tree.h)
