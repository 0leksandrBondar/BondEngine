#include "mainwindow.h"

int main()
{
    const auto window = std::make_unique<Window>(1300, 800, "Hello World!");
    window->startGameLoop();
    return 0;
}
