file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Camera STATIC
        ${Sources})

target_include_directories(
        Camera PUBLIC
        Include)

target_link_libraries(
        Camera PUBLIC
        Interfaces
        OpenGlWrappers
        Utils
        Render
        ResourceManager
)

