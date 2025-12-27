#include "shaderprogram.h"
#include "sprite.h"

#include <window.h>

int main()
{
    const auto window = new BondEngine::Window(1300, 800, "BondEngine");

    const auto shaderProgram = new BondEngine::ShaderProgram("Assets/Shaders/Vertex2D.vert",
                                                             "Assets/Shaders/Fragment2D.frag");

    const auto texture = new BondEngine::Texture2D("Assets/Textures/DefaultTexture.png");
    const auto sprite = new BondEngine::Sprite(shaderProgram, texture, 300, 300);

    window->setFrameCallback([&](const float dt) { window->render(sprite); });

    window->setKeyPressCallback(
        [&](BondEngine::KeyState& state, const float dt)
        {
            constexpr auto speed = 150;

            if (state.isHold(BondEngine::Key::W))
                window->getCamera()->move(0, -speed * dt);
            if (state.isHold(BondEngine::Key::S))
                window->getCamera()->move(0, speed * dt);
            if (state.isHold(BondEngine::Key::A))
                window->getCamera()->move(-speed * dt, 0);
            if (state.isHold(BondEngine::Key::D))
                window->getCamera()->move(speed * dt, 0);
        });

    window->runMainLoop();
    return 0;
}