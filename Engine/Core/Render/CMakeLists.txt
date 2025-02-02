
add_library(Render INTERFACE)

target_link_libraries(
        Render INTERFACE
        Text
        Sprite
        Texture
        Renderer
)

add_subdirectory(Text)
add_subdirectory(Sprite)
add_subdirectory(Texture)
add_subdirectory(Renderer)

