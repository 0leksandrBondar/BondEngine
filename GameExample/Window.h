#pragma once

#include <memory>

namespace BondEngine
{
    class Event;
    class Window;
    class Sprite;
    class Renderer;
    class Camera2D;
    class Texture2D;
} // namespace BondEngine

class Window
{
public:
    Window(int width, int height, const char* title);

    void start() const;

private:
    void setupInputCallbacks();

    void onMouseMove(const BondEngine::Event& event);
    void onMousePress(const BondEngine::Event& event);
    void onMouseRelease(const BondEngine::Event& event);
    void onMouseScroll(const BondEngine::Event& event);

    void onKeyPress(const BondEngine::Event& event);
    void onKeyRelease(const BondEngine::Event& event);

private:
    std::shared_ptr<BondEngine::Window> _window{ nullptr };
    std::shared_ptr<BondEngine::Camera2D> _camera{ nullptr };
    std::shared_ptr<BondEngine::Renderer> _renderer{ nullptr };
};