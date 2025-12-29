file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Sprite STATIC
        ${Sources})

target_include_directories(
        Sprite PUBLIC
        Include)

target_link_libraries(
        Sprite PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
