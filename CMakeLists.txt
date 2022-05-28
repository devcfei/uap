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
    "${PROJECT_SOURCE_DIR}/library/toml11"
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

install(FILES assets/images/demo.png
        CONFIGURATIONS Debug
        DESTINATION Debug/bin
        )

install(FILES assets/images/demo.png
        CONFIGURATIONS Release
        DESTINATION Release/bin
        )

install(FILES source/uiengine/be/imguibe/imgui/misc/fonts/Roboto-Medium.ttf
        CONFIGURATIONS Debug
        DESTINATION Debug/bin
        )

install(FILES source/uiengine/be/imguibe/imgui/misc/fonts/Roboto-Medium.ttf
        CONFIGURATIONS Release
        DESTINATION Release/bin
        )


install(FILES default.toml
        CONFIGURATIONS Debug
        DESTINATION Debug/bin
        )

install(FILES default.toml
        CONFIGURATIONS Release
        DESTINATION Release/bin
        )


