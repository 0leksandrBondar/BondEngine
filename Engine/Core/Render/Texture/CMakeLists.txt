file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Texture STATIC
        ${Sources})

target_include_directories(
        Texture PUBLIC
        include)

target_link_libraries(
        Texture PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
