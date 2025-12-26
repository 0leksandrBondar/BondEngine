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

#include "opengl.h"

#include "Event.h"
#include <functional>

namespace BondEngine
{
    class Window final
    {
        using InputCallback = std::function<void(const Event& event)>;

    public:
        Window(int width, int height, const char* title);
        virtual ~Window() { glfwTerminate(); }

        static void pollEvents() { glfwPollEvents(); }
        void swapBuffers() const { glfwSwapBuffers(_window); }
        void clear(float r, float g, float b, float a = 1.0f);

        void setKeyPressCallback(const InputCallback& callback);
        void setKeyReleaseCallback(const InputCallback& callback);

        void setMouseMoveCallback(const InputCallback& callback);
        void setMousePressCallback(const InputCallback& callback);
        void setMouseScrollCallback(const InputCallback& callback);
        void setMouseReleaseCallback(const InputCallback& callback);

        [[nodiscard]] bool isOpen() const { return !glfwWindowShouldClose(_window); }

    private:
        static void onMouseMove(GLFWwindow* window, double x, double y);
        static void onMouseScroll(GLFWwindow* window, double x, double y);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onKeyboardButton(GLFWwindow* window, int key, int scancode, int action,
                                     int mods);

    private:
        GLFWwindow* _window{ nullptr };

        InputCallback _keyPressCallback;
        InputCallback _keyReleaseCallback;

        InputCallback _mouseMoveCallback;
        InputCallback _mousePressCallback;
        InputCallback _mouseScrollCallback;
        InputCallback _mouseReleaseCallback;
    };
} // namespace BondEngine
