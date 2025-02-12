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

#include "window.h"

#include "utils.h"

#include <MouseEvents.h>

namespace BondEngine
{
    Window::Window(int width, int height, const char* title)
    {
        _window = utils::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        // glfwSetWindowSizeCallback(_window, windowResizeCallback);
        // glfwSetWindowCloseCallback(_window, windowCloseCallback);

        //// keyboard events
        // glfwSetKeyCallback(_window, keyboardButtonCallback);

        //// mouse events
        glfwSetCursorPosCallback(_window, onMouseMove);
        // glfwSetScrollCallback(_window, mouseScrollCallback);
        // glfwSetMouseButtonCallback(_window, mouseButtonCallback);

        utils::initGLAD();
    }

    void Window::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::setMouseMoveCallback(const std::function<void(const Event& event)>& callback)
    {
        _mouseMoveCallback = callback;
    }

    void Window::onMouseMove(GLFWwindow* window, double x, double y)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowPtr->_mouseMoveCallback)
        {
            const MouseMovedEvent event(x, y);
            windowPtr->_mouseMoveCallback(event);
        }
    }

} // namespace BondEngine
