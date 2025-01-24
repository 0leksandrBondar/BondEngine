#include "timer.h"

namespace BondEngine
{

    Timer::Timer() { _lastFrameTime = std::chrono::high_resolution_clock::now(); }

    void Timer::update()
    {
        const auto currentFrameTime = std::chrono::high_resolution_clock::now();

        _deltaTime = std::chrono::duration<float>(currentFrameTime - _lastFrameTime).count();

        _lastFrameTime = currentFrameTime;
    }

} // namespace BondEngine
