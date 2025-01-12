cmake_minimum_required(VERSION 3.20...3.30)

set(GLAD_SOURCES glad/include/glad/glad.h glad/src/glad.c)

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC glad/include)