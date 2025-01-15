cmake_minimum_required(VERSION 3.10)

project(EclipseEngine)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/fmt)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(VOLK_DIR ${CMAKE_SOURCE_DIR}/thirdparty/volk)

include_directories(src)
include_directories(thirdparty/SDL/include)
include_directories(thirdparty/fmt/include)
include_directories(${VOLK_DIR})
include_directories(${Vulkan_INCLUDE_DIRS})
# include_directories(thirdParty/imgui)

add_library(volk STATIC ${VOLK_DIR}/volk.c)

file(GLOB_RECURSE MAIN_SRC src/*)
# file(GLOB SHADERS_SRC src/Shaders/*)

add_executable(EclipseEngine ${MAIN_SRC})

target_link_libraries(EclipseEngine PUBLIC SDL3::SDL3-static fmt::fmt volk)