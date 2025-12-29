file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Text STATIC
        ${Sources})

target_include_directories(
        Text PUBLIC
        Include)

target_link_libraries(
        Text PUBLIC
        Interfaces
        Window
        OpenGlWrappers
        freetype
)
 
