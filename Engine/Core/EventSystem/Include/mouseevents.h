#pragma once

#include "event.h"

namespace BondEngine
{
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(double x, double y);

        [[nodiscard]] double getX() const { return _mouseX; }
        [[nodiscard]] double getY() const { return _mouseY; }

    private:
        double _mouseX, _mouseY;
    };

    /////////////////////////////////////////////////////////

    class MouseScrolledEvent final : public Event
    {
    public:
        explicit MouseScrolledEvent(int offset);

    private:
        int _offset;
    };

    /////////////////////////////////////////////////////////

    class MouseButtonPressedEvent final : public Event
    {
    public:
        explicit MouseButtonPressedEvent(int button);

        [[nodiscard]] bool button(MouseButton button) const;

    private:
        int _button{};
    };

    /////////////////////////////////////////////////////////

    class MouseButtonReleasedEvent final : public Event
    {
    public:
        explicit MouseButtonReleasedEvent(int button);

        [[nodiscard]] bool button(MouseButton button) const;

    private:
        int _button{};
    };

} // namespace BondEngine