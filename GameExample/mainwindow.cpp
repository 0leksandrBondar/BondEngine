#include "mainwindow.h"

#include "glm/ext/scalar_constants.hpp"

Window::Window(const int width, const int height, const char* title)
    : BondEngine::Window(width, height, title),
      _scalingSprite(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png"))),
      _rotationSprite(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png")))
{
    _scalingSprite->setSize(250, 150);
    _rotationSprite->setSize(250, 150);
    _scalingSprite->setPosition(_scalingSprite->getSize().x * 2.f, _rotationSprite->getPosition().y);
}

void Window::draw()
{
    _scalingSprite->draw();
    _rotationSprite->draw();
}

void Window::drawDebugMatrixView()
{
    using namespace std::chrono;

    static auto startTime = high_resolution_clock::now();
    const auto currentTime = high_resolution_clock::now();
    const float elapsedTime = duration<float>(currentTime - startTime).count();

    const float rotation = fmod(elapsedTime * 360.0f / 3.0f, 360.0f);
    _rotationSprite->setRotation(rotation);

    const float scaleFactor = 1.0f + 0.5f * (sin(elapsedTime * glm::pi<float>() / 1.5f));
    _scalingSprite->setScale(scaleFactor, scaleFactor);

    _rotationSprite->draw();
    _scalingSprite->draw();
}

void Window::startGameLoop()
{
    while (!windowShouldClose())
    {
        glClearColor(0.5f, .0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawDebugMatrixView();

        swapBuffers();
        pollEvents();
    }
}

void Window::mouseMoveEvent(const BondEngine::MouseMovedEvent& event) {}

void Window::mousePressEvent(const BondEngine::MouseButtonPressedEvent& event) {}