cmake_minimum_required(VERSION 3.10)
project(uap-uiengine)


aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)


# imgui include
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui)

# imgui
aux_source_directory(${PROJECT_SOURCE_DIR}/be/imguibe/imgui SRCS)



add_library(uiengine SHARED ${SRCS}
    ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends/imgui_impl_dx9.cpp
    ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends/imgui_impl_win32.cpp
)

target_compile_definitions(uiengine PRIVATE UAP_UIENGINE_EXPORTS)
target_link_libraries(uiengine uap)

# backends


# install
install(TARGETS uiengine
        EXPORT uiengineTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uiengine 
        EXPORT uiengineTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )
