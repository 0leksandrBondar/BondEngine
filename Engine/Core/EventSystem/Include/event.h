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

#pragma once

// TODO: add brief for class Event

#include "opengl.h"

#include "glm/vec2.hpp"

#include <string>

namespace BondEngine
{

    enum class EventType
    {
        MouseMoved,
        MouseScrolled,
        MouseButtonPressed,
        MouseButtonReleased,

        KeyPressed,
        KeyReleased,

        WindowClosed,
        WindowResized,

    };

    enum class MouseButton : int
    {
        None = -1,
        Left,
        Right,
        Middle,
    };

    enum class Key : int
    {
        None = -1,
        Key_W = GLFW_KEY_W,
        Key_A = GLFW_KEY_A,
        Key_S = GLFW_KEY_S,
        Key_D = GLFW_KEY_D,
    };

    class Event
    {
    public:
        explicit Event(const EventType type, int button = -1) : _type(type), _button(button) {}
        virtual ~Event() = default;

        [[nodiscard]] EventType getType() const { return _type; }

        virtual bool button(Key button) const { return false; }
        virtual bool button(MouseButton button) const { return false; }
        virtual glm::vec2 getZoomFactor() const { return glm::vec2(0.0f, 0.0f); }
        virtual glm::vec2 getMousePosition() const { return glm::vec2(0.0f, 0.0f); }

    protected:
        EventType _type{};
        int _button{};
    };
} // namespace BondEngine