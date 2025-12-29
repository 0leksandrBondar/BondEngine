file(
        GLOB Sources
        "Include/*.h"
        "Source/*.cpp"
)

add_library(
        Utils STATIC
        ${Sources})

target_include_directories(
        Utils PUBLIC
        Include)

target_link_libraries(
        Utils PUBLIC
        glad
        glfw
        glm
        ResourceManager
)

