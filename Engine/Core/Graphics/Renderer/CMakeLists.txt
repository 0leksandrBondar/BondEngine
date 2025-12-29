file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Renderer STATIC
        ${Sources})

target_include_directories(
        Renderer PUBLIC
        Include)

target_link_libraries(
        Renderer PUBLIC
        Camera
        Interfaces
        OpenGlWrappers
        ResourceManager
)
 
