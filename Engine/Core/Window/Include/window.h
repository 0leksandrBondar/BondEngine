#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "MouseEvents.h"
#include "keyboardevents.h"
#include "windowevents.h"

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
    };
} // namespace BondEngine