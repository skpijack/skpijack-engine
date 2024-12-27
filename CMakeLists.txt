cmake_minimum_required(VERSION 3.10)

project(ModelViewer)

add_subdirectory(thirdParty/glfw)

include_directories(src)
include_directories(thirdParty/glfw/include)

file(GLOB_RECURSE MAIN_SRC src/*)

add_executable(ModelViewer ${MAIN_SRC})

target_link_libraries(ModelViewer PUBLIC glfw)