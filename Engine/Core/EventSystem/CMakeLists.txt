file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
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
        Include)

