cmake_minimum_required(VERSION 3.10)
project(uap-lib)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(uap STATIC ${SRCS})


# install
install(TARGETS uap
        EXPORT uapTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )

