file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Render STATIC
        ${Sources})

target_include_directories(
        Render PUBLIC
        include)

target_link_libraries(
        Render PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
