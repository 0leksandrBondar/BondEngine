file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Interfaces STATIC
        ${Sources})

target_include_directories(
        Interfaces PUBLIC
        include)

        
target_link_libraries(
        Interfaces PUBLIC
        Utils
        OpenGlWrappers
        ResourceManager
)

