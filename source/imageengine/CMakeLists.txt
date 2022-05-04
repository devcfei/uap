cmake_minimum_required(VERSION 3.10)
project(uap-imageengine-top)


# backends

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory("wic")
endif()


if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory("libpng")
endif()

