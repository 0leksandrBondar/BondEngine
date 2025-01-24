file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Tools STATIC
        ${Sources})

target_include_directories(
        Tools PUBLIC
        include)

target_link_libraries(
        Tools PUBLIC
)

