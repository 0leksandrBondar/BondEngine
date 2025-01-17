#include "mainwindow.h"

Window::Window(const int width, const int height, const char* title)
    : BondEngine::Window(width, height, title),
      _sprite(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png"))),
      _sprite2(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png")))
{
    _sprite->setSize(450, 350);
    _sprite2->setSize(450, 350);
}

void Window::draw()
{
    _sprite->draw();
    _sprite2->draw();
}

void Window::startGameLoop()
{
    while (!windowShouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw();

        swapBuffers();
        pollEvents();
    }
}

void Window::mouseMoveEvent(const BondEngine::MouseMovedEvent& event)
{
    _sprite->setPosition(event.getX(), event.getY());
}

void Window::mousePressEvent(const BondEngine::MouseButtonPressedEvent& event) {}