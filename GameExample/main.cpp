#include "Texture2D.h"
#include "renderer.h"
#include "sprite.h"
#include "utils.h"
#include "window.h"

#include <iostream>
#include <window.h>

void mouseMove(const BondEngine::Event& event) { std::cout << "aaaaaaaaaa\n"; }

int main()
{
    const auto window = new Window(1300, 800, "Hello World!");
    window->start();
    return 0;
}
