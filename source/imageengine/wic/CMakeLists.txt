cmake_minimum_required(VERSION 3.10)
project(uap-imageengine)


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)
add_library(imageengine SHARED ${SRCS})
target_compile_definitions(imageengine PRIVATE COMPONENT_EXPORTS)
target_link_libraries(imageengine uap)


# install
install(TARGETS imageengine
        EXPORT imageengineTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


