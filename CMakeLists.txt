cmake_minimum_required(VERSION 3.20...3.30)

project(OpenGLEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Dependencies)
add_subdirectory(Dependencies/glm)
add_subdirectory(Dependencies/glfw)

add_subdirectory(Engine)
add_subdirectory(GameExample)