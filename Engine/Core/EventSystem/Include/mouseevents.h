#pragma once

#include "event.h"

namespace BondEngine
{
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(double x, double y);

        glm::vec2 getMousePosition() const override;

    private:
        double _mouseX, _mouseY;
    };

    /////////////////////////////////////////////////////////

    class MouseScrolledEvent final : public Event
    {
    public:
        explicit MouseScrolledEvent(float offsetX, float offsetY);

        glm::vec2 getZoomFactor() const override;

    private:
        int _offsetX, _offsetY;
    };

    /////////////////////////////////////////////////////////

    class MouseButtonPressedEvent final : public Event
    {
    public:
        explicit MouseButtonPressedEvent(int button);

        bool button(Mouse button) const override;
    };

    /////////////////////////////////////////////////////////

    class MouseButtonReleasedEvent final : public Event
    {
    public:
        explicit MouseButtonReleasedEvent(int button);

        bool button(Mouse button) const override;
    };

} // namespace BondEngine
