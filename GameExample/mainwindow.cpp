#include "mainwindow.h"

Window::Window(const int width, const int height, const char* title)
    : BondEngine::Window(width, height, title)
{
    _texture = std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png");
    _sprite = std::make_shared<BondEngine::Sprite>(_texture);
    _sprite->setSize(450, 350);
    _sprite->setPosition(0, 0);
}

void Window::draw() { _sprite->draw(); }

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