#include "window.h"

#include <iostream>

class Window final : public BondEngine::Window
{
public:
    Window(const int width, const int height, const char* title)
        : BondEngine::Window(width, height, title)
    {
        std::cout << glGetString(GL_RENDERER) << std::endl;
    }
    ~Window() override {}

    void mouseMoveEvent(const BondEngine::MouseMovedEvent& event) override
    {
        // std::cout << "mouseMoveEvent\n";
    }
    void mousePressEvent(const BondEngine::MouseButtonPressedEvent& event) override
    {
        if (event.button(BondEngine::MouseButton::Left))
            std::cout << "mousePressEvent\n";
    }
};

int main()
{
    auto window = std::make_unique<Window>(800, 600, "Hello World!");

  

    while (!window->windowShouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


        window->swapBuffers();
        window->pollEvents();
    }
    return 0;
}
