#pragma once

#include "event.h"

namespace BondEngine
{
    class KeyPressEvent final : public Event
    {
    public:
        explicit KeyPressEvent(int key);

        int _key;
    };

    /////////////////////////////////////////////////////////

    class KeyReleasedEvent final : public Event
    {
    public:
        explicit KeyReleasedEvent(int key);

    private:
        int _key;
    };
} // namespace BondEngine