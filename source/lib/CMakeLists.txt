cmake_minimum_required(VERSION 3.10)
project(uap-library)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(uap STATIC ${SRCS})

# backends

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory("be/windows")
endif()


if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory("be/linux")
endif()

