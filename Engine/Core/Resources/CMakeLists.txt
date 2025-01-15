file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        ResourceManager STATIC
        ${Sources})

target_include_directories(
        ResourceManager PUBLIC
        include)

target_link_libraries(
        ResourceManager PUBLIC
        Interfaces
        OpenGlWrappers
        Utils
        Render
)

