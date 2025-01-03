cmake_minimum_required(VERSION 3.10)

project(ModelViewer)

add_subdirectory(thirdParty/glfw)

include_directories(src)
include_directories(thirdParty/glfw/include)
include_directories(thirdParty/imgui)

file(GLOB MAIN_SRC src/*)
file(GLOB SHADERS_SRC src/Shaders/*)

add_executable(ModelViewer ${MAIN_SRC} ${SHADERS_SRC}
thirdParty/imgui/imgui.cpp 
thirdParty/imgui/imgui_draw.cpp 
thirdParty/imgui/imgui_widgets.cpp 
thirdParty/imgui/imgui_tables.cpp
thirdParty/imgui/backends/imgui_impl_glfw.cpp
thirdParty/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(ModelViewer PUBLIC glfw)