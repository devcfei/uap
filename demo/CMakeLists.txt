cmake_minimum_required(VERSION 3.10)
project(uap-demo)





if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
    aux_source_directory(${PROJECT_SOURCE_DIR}/windows SRCS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")    
endif()


if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
    aux_source_directory(${PROJECT_SOURCE_DIR}/linux SRCS)
endif()


add_executable(demo ${SRCS})
target_link_libraries(demo uap)




# install
install(TARGETS demo
        EXPORT demoTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS demo 
        EXPORT demoTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )
