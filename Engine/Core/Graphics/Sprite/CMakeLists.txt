file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Sprite STATIC
        ${Sources})

target_include_directories(
        Sprite PUBLIC
        include)

target_link_libraries(
        Sprite PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
