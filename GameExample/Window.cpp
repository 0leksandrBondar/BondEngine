#include "Window.h"

#include "camera2d.h"

#include <window.h>

Window::Window(int width, int height, const char* title)
    : _window{ std::make_shared<BondEngine::Window>(width, height, title) },
      _camera{ std::make_shared<BondEngine::Camera2D>() }
{
    setupInputCallbacks();
}

void Window::start() const
{
    while (_window->isOpen())
    {
        _window->clear(0.5f, 1.0f, 0.5f);
        // renderer->render(sprite);
        _window->pollEvents();
        _window->swapBuffers();
    }
}

void Window::onMouseMove(const BondEngine::Event& event) {}

void Window::onMousePress(const BondEngine::Event& event) {}

void Window::onMouseRelease(const BondEngine::Event& event) {}

void Window::onMouseScroll(const BondEngine::Event& event) {}

void Window::onKeyPress(const BondEngine::Event& event) {}

void Window::onKeyRelease(const BondEngine::Event& event) {}

void Window::setupInputCallbacks()
{
    _window->setMouseMoveCallback([this](const BondEngine::Event& event) { onMouseMove(event); });
    _window->setMousePressCallback([this](const BondEngine::Event& event) { onMousePress(event); });
    _window->setMouseReleaseCallback([this](const BondEngine::Event& event)
                                     { onMouseRelease(event); });
    _window->setMouseScrollCallback([this](const BondEngine::Event& event)
                                    { onMouseScroll(event); });
    _window->setKeyPressCallback([this](const BondEngine::Event& event) { onKeyPress(event); });
    _window->setKeyReleaseCallback([this](const BondEngine::Event& event) { onKeyRelease(event); });
}