cmake_minimum_required(VERSION 3.9)
project(Antocoon)


set(CMAKE_CXX_STANDARD 11)
add_executable(Antocoon

        CMakeLists.txt
        main.cpp
        social.cpp
        social.h menu.h menu.cpp
        tree.cpp tree.h)
