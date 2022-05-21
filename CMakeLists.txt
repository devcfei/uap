cmake_minimum_required(VERSION 3.10)
project(uap)


if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    set( my_std_pre "/std:" )
else()
    set( my_std_pre "-std=" )
endif()

set( basic_cxx17 "c++17" )
set( str_cxx17 "${my_std_pre}${basic_cxx17}" )

include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "${str_cxx17}" _cpp_17_flag_supported )
if ( _cpp_17_flag_supported )
    set( CMAKE_CXX_STANDARD 17 )
 endif()

# if( CMAKE_SYSTEM_NAME STREQUAL "Windows")  
#     set(CMAKE_CXX_STANDARD 17 )
# endif()


# if( CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     set(CMAKE_CXX_STANDARD 17 )

# endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/assets/fontawesome"
    )


add_subdirectory(source)
add_subdirectory(test)


# install
install(FILES assets/fontawesome/fontawesome-webfont.ttf
        CONFIGURATIONS Debug
        DESTINATION Debug/bin
        )

install(FILES assets/fontawesome/fontawesome-webfont.ttf
        CONFIGURATIONS Release
        DESTINATION Release/bin
        )


