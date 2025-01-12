file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        OpenGlWrappers STATIC
        ${Sources})

target_include_directories(
        OpenGlWrappers PUBLIC
        include)

target_link_libraries(
        OpenGlWrappers PUBLIC
        Utils 
        Interfaces
)

