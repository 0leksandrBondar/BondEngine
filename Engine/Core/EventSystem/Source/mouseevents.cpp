// MIT License
//
// Copyright (c) 2024 Oleksandr
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "MouseEvents.h"

namespace BondEngine
{
    MouseMovedEvent::MouseMovedEvent(const double x, const double y)
        : Event(EventType::MouseMoved), _mouseX(x), _mouseY(y)
    {
    }

    glm::vec2 MouseMovedEvent::getMousePosition() const { return glm::vec2(_mouseX, _mouseY); }

    MouseScrolledEvent::MouseScrolledEvent(const float offsetX, const float offsetY)
        : Event(EventType::MouseScrolled), _offsetX(offsetX), _offsetY(offsetY)
    {
    }

    glm::vec2 MouseScrolledEvent::getZoomFactor() const { return glm::vec2(_offsetX, _offsetY); }

    MouseButtonPressedEvent::MouseButtonPressedEvent(const int button)
        : Event(EventType::MouseButtonPressed, button)
    {
    }

    bool MouseButtonPressedEvent::button(MouseButton button) const
    {
        return _button == static_cast<int>(button);
    }

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button)
        : Event(EventType::MouseButtonReleased, button)
    {
    }

    bool MouseButtonReleasedEvent::button(MouseButton button) const
    {
        return _button == static_cast<int>(button);
    }

} // namespace BondEngine