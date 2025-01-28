file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Text STATIC
        ${Sources})

target_include_directories(
        Text PUBLIC
        include)

target_link_libraries(
        Text PUBLIC
        Interfaces
        Window
        OpenGlWrappers
)
 
