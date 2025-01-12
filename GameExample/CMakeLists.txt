cmake_minimum_required(VERSION 3.20...3.30)

project(GameExample)

set(SOURCES main.cpp)

add_executable(GameExample ${SOURCES})

target_link_libraries(GameExample PRIVATE
Window
)

set_target_properties(GameExample PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

