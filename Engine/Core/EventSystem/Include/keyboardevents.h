#pragma once

#include "event.h"

namespace BondEngine
{
    class KeyPressEvent final : public Event
    {
    public:
        explicit KeyPressEvent(int key);

       // bool button(Key button) const override;
    };

    /////////////////////////////////////////////////////////

    class KeyReleasedEvent final : public Event
    {
    public:
        explicit KeyReleasedEvent(int key);

        bool button(Key button) const override;
    };
} // namespace BondEngine