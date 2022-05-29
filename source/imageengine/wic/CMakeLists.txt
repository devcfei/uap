cmake_minimum_required(VERSION 3.10)
project(uap-imageengine)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
add_library(imageengine SHARED ${SRCS})
target_compile_definitions(imageengine PRIVATE COMPONENT_EXPORTS)
target_link_libraries(imageengine uap)


# install
install(TARGETS imageengine
        EXPORT imageengineTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS imageengine 
        EXPORT imageengineTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )
