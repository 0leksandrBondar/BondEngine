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

#include "MouseEvents.h"
#include "keyboardevents.h"
#include "utils.h"
#include "windowevents.h"
#include "timer.h"

namespace BondEngine
{
    int Window::_width = 0.0f;
    int Window::_height = 0.0f;

    Window::Window(const int width, const int height, const char* title)
    {
        _width = width;
        _height = height;

        utils::initGLFW();
        _window = utils::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        initCallbacks();
        utils::initGLAD();
        utils::initDefaultResources();
    }

    void Window::startGameLoop()
    {
        Timer timer;
        while (!glfwWindowShouldClose(_window))
        {
            timer.update();
            handleKeyboardEvents();

            updateFrame(timer.getDeltaTime());
            renderFrame();

            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }

    const GLFWwindow* Window::getWindow() const { return _window; }

    void Window::initCallbacks() const
    {
        // window events
        glfwSetWindowSizeCallback(_window, windowResizeCallback);
        glfwSetWindowCloseCallback(_window, windowCloseCallback);

        // mouse events
        glfwSetCursorPosCallback(_window, mouseMovedCallback);
        glfwSetScrollCallback(_window, mouseScrollCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);
    }

    void Window::handleKeyboardEvents()
    {
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
        {
            const int state = glfwGetKey(_window, key);
            if (state == GLFW_PRESS)
            {
                KeyPressEvent event(key);
                keyPressEvent(event);
            }
            else if (state == GLFW_RELEASE)
            {
                KeyReleasedEvent event(key);
                keyReleaseEvent(event);
            }
        }
    }

    void Window::windowCloseCallback(GLFWwindow* window)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        const WindowClosedEvent event;
        windowPtr->windowCloseEvent(event);
    }

    void Window::mouseMovedCallback(GLFWwindow* window, const double x, const double y)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        const MouseMovedEvent event(x, y);
        windowPtr->mouseMoveEvent(event);
    }

    void Window::mouseScrollCallback(GLFWwindow* window, double x, double y)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        const MouseScrolledEvent event(x, y);
        windowPtr->mouseWheelEvent(event);
    }

    void Window::windowResizeCallback(GLFWwindow* window, const int width, const int height)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        const WindowResizedEvent event(width, height);
        windowPtr->windowResizeEvent(event);
        glViewport(0, 0, width, height);
    }

    void Window::mouseButtonCallback(GLFWwindow* window, const int button, const int action,
                                     int mods)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            const MouseButtonPressedEvent event(button);
            windowPtr->mousePressEvent(event);
        }
        else
        {
            const MouseButtonReleasedEvent event(button);
            windowPtr->mouseReleaseEvent(event);
        }
    }

} // namespace BondEngine
