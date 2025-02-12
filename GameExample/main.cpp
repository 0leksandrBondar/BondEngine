#include "Texture2D.h"
#include "renderer.h"
#include "sprite.h"
#include "utils.h"
#include "window.h"

#include <iostream>

void mouseMove(const BondEngine::Event& event) { std::cout << "aaaaaaaaaa\n"; }

int main()
{
    const auto window = new BondEngine::Window(1300, 800, "Hello World!");
    window->setMouseMoveCallback(mouseMove);

    const auto texture = new BondEngine::Texture2D("Assets/Textures/DefaultTexture.png");

    const auto shader = new BondEngine::ShaderProgram("Assets/Shaders/vertexSprite.vert",
                                                      "Assets/Shaders/fragmentSprite.frag");
    const auto sprite = new BondEngine::Sprite(shader, texture);
    const auto renderer = new BondEngine::Renderer(nullptr);

    sprite->setSize(250, 150);

    std::cout << renderer->getGPUBrand();

    while (window->isOpen())
    {
        window->clear(0.5f, 1.0f, 0.5f);

        renderer->render(sprite);

        window->pollEvents();
        window->swapBuffers();
    }

    return 0;
}
