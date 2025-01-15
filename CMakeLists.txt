cmake_minimum_required(VERSION 3.10)

project(EclipseEngine)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/fmt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(src)
include_directories(thirdParty/SDL/include)
include_directories(thirdParty/fmt/include)
# include_directories(thirdParty/imgui)

file(GLOB MAIN_SRC src/*)
file(GLOB SHADERS_SRC src/Shaders/*)

add_executable(EclipseEngine ${MAIN_SRC})

target_link_libraries(EclipseEngine PUBLIC SDL3::SDL3-static fmt::fmt)