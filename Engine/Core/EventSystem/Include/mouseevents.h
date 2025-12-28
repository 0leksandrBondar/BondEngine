#pragma once

#include "event.h"

namespace BondEngine
{
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(double x, double y);

        [[nodiscard]] glm::vec2 getMousePosition() const override;

    private:
        double _mouseX, _mouseY;
    };

    /////////////////////////////////////////////////////////

    class MouseScrolledEvent final : public Event
    {
    public:
        explicit MouseScrolledEvent(double offsetX, double offsetY);

        [[nodiscard]] glm::vec2 getZoomFactor() const override;

    private:
        double _offsetX, _offsetY;
    };

    /////////////////////////////////////////////////////////

    class MouseButtonPressedEvent final : public Event
    {
    public:
        explicit MouseButtonPressedEvent(int button);

        [[nodiscard]] bool button(Mouse button) const override;
    };

    /////////////////////////////////////////////////////////

    class MouseButtonReleasedEvent final : public Event
    {
    public:
        explicit MouseButtonReleasedEvent(int button);

        bool button(Mouse button) const override;
    };

} // namespace BondEngine
