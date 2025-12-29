file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        OpenGlWrappers STATIC
        ${Sources})

target_include_directories(
        OpenGlWrappers PUBLIC
        Include)

target_link_libraries(
        OpenGlWrappers PUBLIC
        Utils 
        Interfaces
)

