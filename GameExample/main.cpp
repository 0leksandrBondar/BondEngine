#include "mainwindow.h"

int main()
{
    const auto window = std::make_unique<Window>(800, 600, "Hello World!");
    window->startGameLoop();
    return 0;
}
