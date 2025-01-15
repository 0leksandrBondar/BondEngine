#include "window.h"

#include <iostream>
#include <sprite.h>
#include <texture2D.h>

class Window final : public BondEngine::Window
{
public:
    Window(const int width, const int height, const char* title)
        : BondEngine::Window(width, height, title)
    {
        std::cout << glGetString(GL_RENDERER) << std::endl;
        _texture = std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png");
        _sprite = std::make_shared<BondEngine::Sprite>(_texture);
        _sprite->setSize(450, 350);
        _sprite->setPosition(0, 0);
    }

    ~Window() override {}

    void draw() { _sprite->draw(); }

    void mouseMoveEvent(const BondEngine::MouseMovedEvent& event) override
    {
        std::cout << event.getX() << " : " << event.getY() << std::endl;
        _sprite->setPosition(event.getX(), event.getY());
    }
    void mousePressEvent(const BondEngine::MouseButtonPressedEvent& event) override
    {
        if (event.button(BondEngine::MouseButton::Left))
            std::cout << "mousePressEvent\n";
    }

private:
    std::shared_ptr<BondEngine::Sprite> _sprite;
    std::shared_ptr<BondEngine::Texture2D> _texture;
};

int main()
{
    const auto window = std::make_unique<Window>(800, 600, "Hello World!");

    while (!window->windowShouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window->draw();

        window->swapBuffers();
        window->pollEvents();
    }
    return 0;
}
