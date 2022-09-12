cmake_minimum_required(VERSION 3.10)
project(uap-uiengine)



# uiengine source
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)


# imgui include
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui)
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends)



# imgui source
aux_source_directory(${PROJECT_SOURCE_DIR}/be/imguibe/imgui SRCS)


# imgui extra source
set(SRC_EXTRA
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends/imgui_impl_dx9.cpp
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends/imgui_impl_dx11.cpp
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/backends/imgui_impl_win32.cpp 
)


# freetype include
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui/misc/freetype)
# freetype source
list(APPEND SRC_EXTRA 
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui/misc/freetype/imgui_freetype.cpp
)


# imgui_tex_inspect include
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect)
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect/backends)
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect/examples/loaders)

# imgui_tex_inspect source
#aux_source_directory(${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect SRCS)




# imgui_tex_inspect source
list(APPEND SRC_EXTRA 
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect/backends/tex_inspect_directx11.cpp 
     ${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect/imgui_tex_inspect.cpp 
     #${PROJECT_SOURCE_DIR}/be/imguibe/imgui_tex_inspect/imgui_tex_inspect_demo.cpp 
)



# implot
include_directories(${PROJECT_SOURCE_DIR}/be/imguibe/implot)
aux_source_directory(${PROJECT_SOURCE_DIR}/be/imguibe/implot SRCS)


add_library(uiengine SHARED ${SRCS} ${SRC_EXTRA} )


target_compile_definitions(uiengine PRIVATE COMPONENT_EXPORTS)
target_link_libraries(uiengine uap d3d9 d3d11 d3dcompiler dxgi)
target_link_libraries(uiengine freetype)

# backends


# install
install(TARGETS uiengine
        EXPORT uiengineTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uiengine 
        EXPORT uiengineTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
