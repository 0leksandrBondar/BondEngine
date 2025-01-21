file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        EventSystem STATIC
        ${Sources})

target_link_libraries(
        EventSystem PUBLIC
        Utils
)

target_include_directories(
        EventSystem PUBLIC
        include)

