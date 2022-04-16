cmake_minimum_required(VERSION 3.10)
project(uap-demo)

aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

add_executable(demo ${SRCS})