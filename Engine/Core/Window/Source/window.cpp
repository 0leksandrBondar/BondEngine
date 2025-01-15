#include "window.h"

#include "MouseEvents.h"
#include "keyboardevents.h"
#include "utils.h"
#include "windowevents.h"

#include <iostream>

namespace BondEngine
{

    Window::Window(const int width, const int height, const char* title)
    {
        utils::initGLFW();
        _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!_window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        initCallbacks();

        if (!utils::initGLAD())
            std::cerr << "Failed to initialize GLAD" << std::endl;

        utils::initDefaultResources();
    }

    Window::~Window() { glfwTerminate(); }

    void Window::pollEvents() const { glfwPollEvents(); }

    void Window::swapBuffers() const { glfwSwapBuffers(_window); }

    const GLFWwindow* Window::getWindow() const { return _window; }

    int Window::windowShouldClose() const { return glfwWindowShouldClose(_window); }

    void Window::initCallbacks() const
    {
        // window events
        glfwSetWindowSizeCallback(_window, windowResizeCallback);
        glfwSetWindowCloseCallback(_window, windowCloseCallback);

        // keyboard events
        glfwSetKeyCallback(_window, keyboardButtonCallback);

        // mouse events
        glfwSetCursorPosCallback(_window, mouseMovedCallback);
        glfwSetScrollCallback(_window, mouseScrollCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);
    }

    void Window::windowCloseCallback(GLFWwindow* window)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        WindowClosedEvent event;
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
        MouseScrolledEvent event(y);
        windowPtr->mouseWheelEvent(event);
    }

    void Window::windowResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        WindowResizedEvent event(width, height);
        windowPtr->windowResizeEvent(event);
        glViewport(0, 0, width, height);
    }

    void Window::mouseButtonCallback(GLFWwindow* window, const int button, const int action,
                                     int mods)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            MouseButtonPressedEvent event(button);
            windowPtr->mousePressEvent(event);
        }
        else
        {
            MouseButtonReleasedEvent event(button);
            windowPtr->mouseReleaseEvent(event);
        }
    }

    void Window::keyboardButtonCallback(GLFWwindow* window, const int key, int scancode,
                                        const int action, int mods)
    {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            KeyPressEvent event(key);
            windowPtr->keyPressEvent(event);
        }
        else if (action == GLFW_RELEASE)
        {
            KeyReleasedEvent event(key);
            windowPtr->keyReleaseEvent(event);
        }
    }

} // namespace BondEngine