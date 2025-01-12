#include "keyboardevents.h"

namespace BondEngine
{

    KeyPressEvent::KeyPressEvent(const int key) : Event(EventType::KeyPressed), _key(key) {}

    KeyReleasedEvent::KeyReleasedEvent(const int key) : Event(EventType::KeyReleased), _key(key) {}

} // namespace BondEngine