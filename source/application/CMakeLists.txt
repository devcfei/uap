cmake_minimum_required(VERSION 3.10)
project(uap-application)



# include



# source 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/windows SRCS)
endif()


if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/linux SRCS)
endif()


add_library(application SHARED ${SRCS})

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/windows )
endif()

if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_include_directories(application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/linux )
endif()

target_include_directories(application PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_definitions(application PRIVATE COMPONENT_EXPORTS)
target_link_libraries(application uap)
if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(application shlwapi )
endif()

# install
install(TARGETS application
        EXPORT applicationTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )



