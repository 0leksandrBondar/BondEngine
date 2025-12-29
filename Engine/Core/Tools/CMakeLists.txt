file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Tools STATIC
        ${Sources})

target_include_directories(
        Tools PUBLIC
        Include)

target_link_libraries(
        Tools PUBLIC
)

