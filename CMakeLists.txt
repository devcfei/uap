cmake_minimum_required(VERSION 3.10)
project(uap)


# Build options
option(BUILD_TEST "Build Test" ON)
option(BUILD_DEMO "Build Demo" ON)


# C++ flags
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "${str_cxx17}" _cpp_17_flag_supported )
if ( _cpp_17_flag_supported )
    set( CMAKE_CXX_STANDARD 17 )
endif()



# global include
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/fontawesome/5.15.4"
    "${CMAKE_CURRENT_SOURCE_DIR}/library/toml11"
    "${CMAKE_CURRENT_SOURCE_DIR}/library/freetype/include"
    )

    



# subdirectories
add_subdirectory(library)
add_subdirectory(source)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_DEMO)
    add_subdirectory(demo)
endif()


# install
install(FILES assets/fontawesome/5.15.4/fa-solid-900.ttf
        DESTINATION bin
        )


install(FILES default.toml
        DESTINATION bin
        )


