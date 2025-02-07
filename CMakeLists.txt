cmake_minimum_required(VERSION 3.10)

project(EclipseEngine)

set(EXTERNAL_INCLUDES src/external)

add_subdirectory(${EXTERNAL_INCLUDES}/glfw)
add_subdirectory(${EXTERNAL_INCLUDES}/fmt)

include_directories(src)
include_directories(${EXTERNAL_INCLUDES})
include_directories(${EXTERNAL_INCLUDES}/glfw/include)
include_directories(${EXTERNAL_INCLUDES}/imgui)
# include_directories(thirdParty/implot)

file(GLOB_RECURSE MAIN_SRC src/Eclipse*/*)
file(GLOB SHADERS_SRC src/Shaders/*)

add_library(imgui 
    ${EXTERNAL_INCLUDES}/imgui/imgui.cpp 
    ${EXTERNAL_INCLUDES}/imgui/imgui_draw.cpp 
    ${EXTERNAL_INCLUDES}/imgui/imgui_widgets.cpp 
    ${EXTERNAL_INCLUDES}/imgui/imgui_tables.cpp
    ${EXTERNAL_INCLUDES}/imgui/backends/imgui_impl_glfw.cpp
    ${EXTERNAL_INCLUDES}/imgui/backends/imgui_impl_opengl3.cpp
)

# add_library(implot thirdParty/implot/implot.cpp thirdParty/implot/implot_items.cpp)

add_executable(EclipseEngine ${MAIN_SRC} ${SHADERS_SRC})

target_link_libraries(EclipseEngine PUBLIC glfw PUBLIC imgui PUBLIC fmt)