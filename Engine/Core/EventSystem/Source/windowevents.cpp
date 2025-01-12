#include "windowevents.h"

namespace BondEngine
{

    WindowResizedEvent::WindowResizedEvent(int width, int height)
        : Event(EventType::WindowResized), _width(width), _height(height)
    {
    }

    WindowClosedEvent::WindowClosedEvent() : Event(EventType::WindowClosed) {}

} // namespace BondEngine