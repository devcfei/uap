cmake_minimum_required(VERSION 3.10)
project(uap-application)



# include



# source 
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    aux_source_directory(${PROJECT_SOURCE_DIR}/windows SRCS)
endif()


if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    aux_source_directory(${PROJECT_SOURCE_DIR}/linux SRCS)
endif()


add_library(application SHARED ${SRCS})

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(application PRIVATE ${PROJECT_SOURCE_DIR}/windows )
endif()

if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_include_directories(application PRIVATE ${PROJECT_SOURCE_DIR}/linux )
endif()

target_include_directories(application PRIVATE ${PROJECT_SOURCE_DIR} )
target_compile_definitions(application PRIVATE COMPONENT_EXPORTS)
target_link_libraries(application uap)


# install
install(TARGETS application
        EXPORT applicationTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS application 
        EXPORT applicationTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
