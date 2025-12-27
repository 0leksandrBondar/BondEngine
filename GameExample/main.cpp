#include "sprite.h"

#include <window.h>

int main()
{
    const auto window = new BondEngine::Window(1300, 800, "BondEngine");

    const auto sprite = new BondEngine::Sprite();
    sprite->setSize(300, 300);

    window->setFrameCallback([&](const float dt) { window->render(sprite); });

    window->runMainLoop();
    return 0;
}