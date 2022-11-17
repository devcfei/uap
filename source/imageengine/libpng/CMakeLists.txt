cmake_minimum_required(VERSION 3.10)
project(uap-imageengine)


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)
add_library(imageengine SHARED ${SRCS})


# install
install(TARGETS imageengine
        EXPORT imageengineTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


