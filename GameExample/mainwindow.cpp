#include "mainwindow.h"

#include "camera2d.h"
#include "glm/ext/scalar_constants.hpp"
#include "sprite.h"
#include "texture2D.h"

Window::Window(const int width, const int height, const char* title)
    : BondEngine::Window(width, height, title),
      _camera{ std::make_shared<BondEngine::Camera2D>() },
      _scalingSprite(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png"))),
      _rotationSprite(std::make_shared<BondEngine::Sprite>(
          std::make_shared<BondEngine::Texture2D>("assets/Textures/DefaultTexture.png")))
{
    _scalingSprite->setSize(250, 150);
    _rotationSprite->setSize(250, 150);
    _scalingSprite->setPosition(_scalingSprite->getSize().x * 2.f,
                                _rotationSprite->getPosition().y);
}

void Window::draw() const
{
    _scalingSprite->draw();
    _rotationSprite->draw();
}

void Window::updateFrame(const float deltaTime)
{
    constexpr float rotationSpeed = 120.0f;
    constexpr float scalingFrequency = 2.0f;
    constexpr float scalingAmplitude = 0.5f;
    constexpr float baseScale = 1.0f;

    static float currentRotation = 0.0f;
    currentRotation += rotationSpeed * deltaTime;
    currentRotation = fmod(currentRotation, 360.0f);
    _rotationSprite->setRotation(currentRotation);

    static float scalingTime = 0.0f;
    scalingTime += deltaTime;
    const float scaleFactor
        = baseScale + scalingAmplitude * sin(scalingTime * scalingFrequency * glm::pi<float>());
    _scalingSprite->setScale(scaleFactor, scaleFactor);

    _camera->update();
}

void Window::renderFrame()
{
    glClearColor(0.5f, 1.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw();
}

void Window::keyPressEvent(const BondEngine::Event& event)
{
    if (event.button(BondEngine::Key::W))
        _camera->move(0.f, 0.2);
    if (event.button(BondEngine::Key::S))
        _camera->move(0.f, -0.2);
    if (event.button(BondEngine::Key::A))
        _camera->move(0.2, 0);
    if (event.button(BondEngine::Key::D))
        _camera->move(-0.2, 0);
}

void Window::mouseWheelEvent(const BondEngine::Event& event)
{
    const auto zoomFactor = event.getZoomFactor();
    float scaleFactor = 1.0f + zoomFactor.y * 0.1f; // Use only y-component for vertical scrolling
    glm::vec2 screenCenter = { Window::getWidth() / 2.0f, Window::getHeight() / 2.0f };

    if (scaleFactor < 0.1f)
        scaleFactor = 0.1f;

    _camera->zoom(scaleFactor,screenCenter);
}
