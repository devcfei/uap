cmake_minimum_required(VERSION 3.10)
project(uapbe-library)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(uapbe SHARED ${SRCS})
target_compile_definitions(uapbe PRIVATE UAPBE_EXPORTS)


# install
install(TARGETS uapbe
        EXPORT uapbeTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uapbe 
        EXPORT uapbeTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )
