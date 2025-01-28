
add_library(Render INTERFACE)

target_link_libraries(
        Render INTERFACE
        Texture
        Sprite
        Text
)

add_subdirectory(Text)
add_subdirectory(Sprite)
add_subdirectory(Texture)

