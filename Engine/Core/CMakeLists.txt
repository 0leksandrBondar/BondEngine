add_library(Core INTERFACE)

target_link_libraries(Core INTERFACE
        INTERFACES
)

add_library(BondEngine::Core ALIAS Core)

add_subdirectory(Utils)
add_subdirectory(Window)
add_subdirectory(Interfaces)
add_subdirectory(EventSystem)
add_subdirectory(OpenGLWrap)



