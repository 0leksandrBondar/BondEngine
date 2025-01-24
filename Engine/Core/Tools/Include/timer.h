#pragma once

#include <chrono>

namespace BondEngine
{
    class Timer
    {
    public:
        Timer();

        void update();

        [[nodiscard]] float getDeltaTime() const { return _deltaTime; }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime;
        float _deltaTime = 0.0f;
    };
} // namespace BondEngine
