file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Renderer STATIC
        ${Sources})

target_include_directories(
        Renderer PUBLIC
        include)

target_link_libraries(
        Renderer PUBLIC
        Camera
        Interfaces
        OpenGlWrappers
        ResourceManager
)
 
