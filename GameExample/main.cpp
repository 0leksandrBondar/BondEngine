#include "renderer.h"
#include "shaderprogram.h"
#include "sprite.h"

#include <window.h>

int main()
{
    const auto window = new BondEngine::Window(1300, 800, "BondEngine");

    const auto shaderProgram2 = new BondEngine::ShaderProgram("Assets/Shaders/Vertex2D.vert",
                                                              "Assets/Shaders/Fragment2D.frag");

    const auto texture = new BondEngine::Texture2D("Assets/Textures/DefaultTexture.png");
    const auto sprite = new BondEngine::Sprite(shaderProgram2, texture, 300, 300);

    const auto camera = new BondEngine::Camera2D();
    const auto renderer = new BondEngine::Renderer(camera);

    sprite->setPosition({650.f, 400.f});

    glm::vec2 viewportSize = {1300.f, 800.f};
    camera->setPosition(sprite->getPosition() - viewportSize * 0.5f);



    window->setKeyPressCallback(
        [&sprite, &camera](const BondEngine::Event& event)
        {
            if (event.button(BondEngine::Key::E))
            {
                sprite->move(0,10);
            }

            if (event.button(BondEngine::Key::W))
            {
                camera->move(0,10);
            }
            if (event.button(BondEngine::Key::A))
            {
                camera->move(-10,0);
            }
            if (event.button(BondEngine::Key::S))
            {
                camera->move(0,-10);
            }
            if (event.button(BondEngine::Key::D))
            {
                camera->move(10,0);
            }
        });

    while (window->isOpen())
    {
        window->clear(0.2f, 0.3f, 0.3f, 1.0f);

        renderer->render(sprite);

        window->swapBuffers();
        BondEngine::Window::pollEvents();
    }
    return 0;
}
