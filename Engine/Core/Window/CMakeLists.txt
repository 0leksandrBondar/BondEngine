file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)


add_library(
        Window STATIC
        ${Sources})

target_include_directories(
        Window PUBLIC
        Include)

target_link_libraries(
        Window PUBLIC
        EventSystem
        Utils
        Tools
)
 
