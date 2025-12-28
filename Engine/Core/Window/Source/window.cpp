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

#include "inputstate.h"
#include "resourcemanager.h"
#include "utils.h"

#include <MouseEvents.h>

namespace BondEngine
{
    Window::Window(const int width, const int height, const char* title)
        : _windowSize(width, height),
          _camera2D{ std::make_shared<Camera2D>(width, height) },
          _renderer{ std::make_shared<Renderer>(_camera2D.get(), this) }
    {
        _window = utils::createWindow(width, height, title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        // glfwSetWindowSizeCallback(_window, windowResizeCallback);
        // glfwSetWindowCloseCallback(_window, windowCloseCallback);

        //// keyboard events
        glfwSetKeyCallback(_window, onKeyboardButton);

        //// mouse events
        glfwSetScrollCallback(_window, onMouseScroll);
        glfwSetCursorPosCallback(_window, onMouseMove);
        glfwSetMouseButtonCallback(_window, onMouseButton);

        utils::initGLAD();

        initializeDefaultLibData();
    }

    void Window::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::render(Drawable* drawableItem) const
    {
        if (_renderer)
            _renderer->render(drawableItem);
    }

    void Window::runMainLoop()
    {
        while (isOpen())
        {
            _timer.update();
            const float dt = _timer.getDeltaTime();
            clear(0.2f, 0.3f, 0.3f, 1.0f);

            handleKeyboardInputEvent(dt);

            if (_frameCallback)
                _frameCallback(dt);

            _keyState._previous = _keyState._current;

            swapBuffers();
            glfwPollEvents();
        }
    }

    void Window::setFrameCallback(const FrameCallback& frameCallback)
    {
        _frameCallback = frameCallback;
    }

    void Window::setKeyPressCallback(const KeyHoldCallback& callback)
    {
        _keyHoldCallback = callback;
    }

    void Window::setMouseMoveCallback(const InputCallback& callback)
    {
        _mouseMoveCallback = callback;
    }

    void Window::setMousePressCallback(const InputCallback& callback)
    {
        _mousePressCallback = callback;
    }

    void Window::setMouseScrollCallback(const InputCallback& callback)
    {
        _mouseScrollCallback = callback;
    }

    void Window::setMouseReleaseCallback(const InputCallback& callback)
    {
        _mouseReleaseCallback = callback;
    }

    void Window::loadDefaultShaders()
    {
        ResourceManager::getInstance()->loadShaderProgram("default", "Assets/Shaders/Vertex2D.vert",
                                                          "Assets/Shaders/Fragment2D.frag");
    }

    void Window::loadDefaultTextures()
    {
        ResourceManager::getInstance()->loadTexture2D("default",
                                                      "Assets/Textures/DefaultTexture.png");
    }

    void Window::initializeDefaultLibData()
    {
        loadDefaultShaders();
        loadDefaultTextures();
    }

    void Window::handleKeyboardInputEvent(const float dt)
    {
        if (_keyHoldCallback)
            _keyHoldCallback(_keyState, dt);
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

    void Window::onMouseScroll(GLFWwindow* window, double x, double y)
    {
        const auto windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (windowPtr->_mouseScrollCallback)
        {
            const MouseScrolledEvent event(x, y);
            windowPtr->_mouseScrollCallback(event);
        }
    }

    void Window::onMouseButton(GLFWwindow* window, int button, int action, int mods)
    {
        const auto windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            if (windowPtr->_mousePressCallback)
            {
                const MouseButtonPressedEvent event(button);
                windowPtr->_mousePressCallback(event);
            }
        }
        else
        {
            if (windowPtr->_mouseReleaseCallback)
            {
                const MouseButtonReleasedEvent event(button);
                windowPtr->_mouseReleaseCallback(event);
            }
        }
    }

    void Window::onKeyboardButton(GLFWwindow* window, int key, int, int action, int)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        Key k = static_cast<Key>(key);

        if (action == GLFW_PRESS)
            self->_keyState._current[k] = true;
        else if (action == GLFW_RELEASE)
            self->_keyState._current[k] = false;
    }

} // namespace BondEngine
