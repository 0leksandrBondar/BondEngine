file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Utils STATIC
        ${Sources})

target_include_directories(
        Utils PUBLIC
        include)

target_link_libraries(
        Utils PUBLIC
        glad
        glfw
        glm
        ResourceManager
)

