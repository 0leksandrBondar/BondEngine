#pragma once

#include "sprite.h"
#include "texture2D.h"
#include "window.h"

class Window final : public BondEngine::Window
{
public:
    Window(const int width, const int height, const char* title);

    ~Window() override = default;

    void draw();
    void startGameLoop();

    void mouseMoveEvent(const BondEngine::MouseMovedEvent& event) override;
    void mousePressEvent(const BondEngine::MouseButtonPressedEvent& event) override;

private:
    std::shared_ptr<BondEngine::Sprite> _sprite;
    std::shared_ptr<BondEngine::Sprite> _sprite2;
};