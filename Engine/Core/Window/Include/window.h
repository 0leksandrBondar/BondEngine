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

#include "MouseEvents.h"
#include "keyboardevents.h"
#include "windowevents.h"

#include "opengl.h"

namespace BondEngine
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        virtual ~Window();

        void pollEvents() const;
        void swapBuffers() const;

        [[nodiscard]] const GLFWwindow* getWindow() const;
        [[nodiscard]] int windowShouldClose() const;

        virtual void mouseMoveEvent(const MouseMovedEvent& event) {}
        virtual void mouseWheelEvent(const MouseScrolledEvent& event) {}
        virtual void mousePressEvent(const MouseButtonPressedEvent& event) {}
        virtual void mouseReleaseEvent(const MouseButtonReleasedEvent& event) {}

        virtual void keyPressEvent(const KeyPressEvent& event) {}
        virtual void keyReleaseEvent(const KeyReleasedEvent& event) {}

        virtual void windowCloseEvent(const WindowClosedEvent& event) {}
        virtual void windowResizeEvent(const WindowResizedEvent& event) {}

        static float getWidth() { return _width; };
        static float getHeight() { return _height; };

    private:
        void initCallbacks() const;

        static void windowCloseCallback(GLFWwindow* window);
        static void mouseMovedCallback(GLFWwindow* window, double x, double y);
        static void mouseScrollCallback(GLFWwindow* window, double x, double y);
        static void windowResizeCallback(GLFWwindow* window, int width, int height);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void keyboardButtonCallback(GLFWwindow* window, int key, int scancode, int action,
                                           int mods);

    private:
        std::string _title{};
        GLFWwindow* _window{ nullptr };

    private:
        static float _width, _height;
    };
} // namespace BondEngine