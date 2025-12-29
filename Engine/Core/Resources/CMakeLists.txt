file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        ResourceManager STATIC
        ${Sources})

target_include_directories(
        ResourceManager PUBLIC
        Include)

target_link_libraries(
        ResourceManager PUBLIC
        Interfaces
        OpenGlWrappers
        Utils
        Render
)

