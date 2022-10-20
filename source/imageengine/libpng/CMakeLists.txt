cmake_minimum_required(VERSION 3.10)
project(uap-imageengine)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(imageengine SHARED ${SRCS})


# install
install(TARGETS imageengine
        EXPORT imageengineTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS imageengine 
        EXPORT imageengineTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
