cmake_minimum_required(VERSION 3.10)
project(uap-lib)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(uap STATIC ${SRCS})


# install
install(TARGETS uap
        EXPORT uapTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uap 
        EXPORT uapTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )

