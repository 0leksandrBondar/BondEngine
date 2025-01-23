#pragma once

#include "buttonsdefenition.h"

namespace BondEngine
{
    class EventHandler
    {
    public:
        static bool isKeyPressed(Mouse button);
        static bool isKeyPressed(Keyboard key);
        // static bool isKeyReleased(Mouse button);
        // static bool isKeyReleased(Keyboard key);
    };
} // namespace BondEngine
