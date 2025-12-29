file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Interfaces STATIC
        ${Sources})

target_include_directories(
        Interfaces PUBLIC
        Include)

        
target_link_libraries(
        Interfaces PUBLIC
        Utils
        OpenGlWrappers
        ResourceManager
)

