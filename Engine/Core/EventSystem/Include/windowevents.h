#pragma once
#include "event.h"

namespace BondEngine
{
    class WindowResizedEvent final : public Event
    {
    public:
        WindowResizedEvent(int width, int height);

    private:
        int _width, _height;
    };

    /////////////////////////////////////////////////////////

    class WindowClosedEvent final : public Event
    {
    public:
        WindowClosedEvent();
    };
} // namespace BondEngine