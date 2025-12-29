file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Texture STATIC
        ${Sources})

target_include_directories(
        Texture PUBLIC
        Include)

target_link_libraries(
        Texture PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
