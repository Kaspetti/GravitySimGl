cmake_minimum_required(VERSION 3.10)

project(GravitySim)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(GravitySim cmd/main.cpp shaders/shaders.cpp)

target_link_libraries(GravitySim PRIVATE GLEW::GLEW glfw glm::glm)
