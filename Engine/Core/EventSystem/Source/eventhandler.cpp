#include "eventhandler.h"

namespace BondEngine
{
    bool EventHandler::isKeyPressed(Mouse button)
    {
        if (GetKeyState(static_cast<int>(button)) < 0)
            return true;
        return false;
    }

    bool EventHandler::isKeyPressed(Keyboard key)
    {
        if (GetKeyState(static_cast<int>(key)) < 0)
            return true;
        return false;
    }

} // namespace BondEngine
