cmake_minimum_required(VERSION 3.10)
project(uap-imageengine)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(imageengine SHARED ${SRCS})


# install
install(TARGETS imageengine
        EXPORT imageengineTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS imageengine 
        EXPORT imageengineTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
