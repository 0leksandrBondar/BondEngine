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

#include "camera2d.h"

#include "GLFW/glfw3.h"
#include "event.h"
#include "resourcemanager.h"
#include "window.h"

#include <iostream>

namespace BondEngine
{

    Camera2D::Camera2D()
    {
        _shaderProgram = ResourceManager::getInstance()->getShaderProgram("DefaultShaderProgram");
        _shaderProgram->use();
        _shaderProgram->setMatrix4("viewMat", glm::mat4(1.0f));
    }

    void Camera2D::zoom(float scaleFactorX, float scaleFactorY)
    {
        _scale *= glm::vec2(scaleFactorX, scaleFactorY);

        if (_scale.x < 0.1f)
            _scale.x = 0.1f;
        if (_scale.y < 0.1f)
            _scale.y = 0.1f;

        _shaderProgram->setMatrix4("viewMat", getViewMatrix());
    }

    void Camera2D::move(const Event& event)
    {
        if (event.button(Key::Key_W))
            Transformable::move(0.f, -_speed);
        if (event.button(Key::Key_S))
            Transformable::move(0.f, _speed);
        if (event.button(Key::Key_A))
            Transformable::move(_speed, 0);
        if (event.button(Key::Key_D))
            Transformable::move(-_speed, 0);

        _shaderProgram->setMatrix4("viewMat", getViewMatrix());
    }

    glm::mat4 Camera2D::getViewMatrix()
    {
        glm::vec2 screenCenter = { Window::getWidth() / 2.0f, Window::getHeight() / 2.0f };

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(screenCenter, 0.0f));
        view = glm::scale(view, glm::vec3(_scale.y, _scale.y, 0.0f));
        view = glm::translate(view, glm::vec3(-screenCenter + _position, -3.0f));

        return view;
    }

    glm::mat4 Camera2D::getProjectionMatrix(int width, int height) const
    {
        return glm::ortho(0.0f, float(width), float(height), 0.0f, 0.1f, 100.0f);
    }
} // namespace BondEngine