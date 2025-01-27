#pragma once

#include "window.h"

#include <memory>

namespace BondEngine
{
    class Sprite;
    class Camera2D;
} // namespace BondEngine

class Window final : public BondEngine::Window
{
public:
    Window(const int width, const int height, const char* title);

    ~Window() override = default;

    void draw() const;

    void renderFrame() override;
    void updateFrame(const float deltaTime) override;

    void keyPressEvent(const BondEngine::Event& event) override;
    void mouseWheelEvent(const BondEngine::Event& event) override;

private:
    std::shared_ptr<BondEngine::Camera2D> _camera;
    std::shared_ptr<BondEngine::Sprite> _scalingSprite;
    std::shared_ptr<BondEngine::Sprite> _rotationSprite;
};
