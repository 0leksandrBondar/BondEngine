#include "keyboardevents.h"

namespace BondEngine
{

    KeyPressEvent::KeyPressEvent(const int key) : Event(EventType::KeyPressed, key) {}

    bool KeyPressEvent::button(Key button) const { return _button == static_cast<int>(button); }

    KeyReleasedEvent::KeyReleasedEvent(const int key) : Event(EventType::KeyReleased, key) {}

    bool KeyReleasedEvent::button(Key button) const { return _button == static_cast<int>(button); }

} // namespace BondEngine
