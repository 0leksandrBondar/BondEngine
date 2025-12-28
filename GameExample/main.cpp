#include "sprite.h"

#include <window.h>

#include "inputstate.h"

class Window
{
public:
    Window(const int width, const int height, const char* title)
        : _window{ new BondEngine::Window(width, height, title) },
          _sprite{ new BondEngine::Sprite() }
    {
        _sprite->useDefaultTexture();
        _sprite->setSize(300, 300);
        setupCallbacks();
    }

    void runMainLoop() const { _window->runMainLoop(); }

private:
    void onKeyEvent(BondEngine::KeyState& state, float deltaTime)
    {
        auto speed = 200.f;

        if (state.isHold(BondEngine::Key::LShift))
            speed *= 3;
        else if (state.isReleased(BondEngine::Key::LShift))
            speed /= 3;

        if (state.isPressed(BondEngine::Key::Space))
            _window->getCamera()->setRotation(45);

        if (state.isHold(BondEngine::Key::W))
            _window->getCamera()->move({ 0.f, -speed * deltaTime });
        if (state.isHold(BondEngine::Key::A))
            _window->getCamera()->move({ -speed * deltaTime, 0.f });
        if (state.isHold(BondEngine::Key::S))
            _window->getCamera()->move({ 0.f, speed * deltaTime });
        if (state.isHold(BondEngine::Key::D))
            _window->getCamera()->move({ speed * deltaTime, 0.f });
    }

    void onFrameEvent(const float deltaTime) { _window->render(_sprite); }

    void setupCallbacks()
    {
        _window->setKeyPressCallback([this](BondEngine::KeyState& state, float deltaTime)
                                     { onKeyEvent(state, deltaTime); });
        _window->setFrameCallback([this](const float deltaTime) { onFrameEvent(deltaTime); });
    }

private:
    BondEngine::Window* _window{ nullptr };
    BondEngine::Sprite* _sprite{ nullptr };
};

int main()
{
    const auto window = Window(1300, 800, "BondEngine");

    window.runMainLoop();
    return 0;
}