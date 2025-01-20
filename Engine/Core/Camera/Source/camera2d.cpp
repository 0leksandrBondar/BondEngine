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
#include "resourcemanager.h"

#include <iostream>

namespace BondEngine
{

    Camera2D::Camera2D()
    {
        _shaderProgram = ResourceManager::getInstance()->getShaderProgram("DefaultShaderProgram");
        _shaderProgram->use();
        _shaderProgram->setMatrix4("viewMat", glm::mat4(1.0f));
    }

    void Camera2D::move(const KeyPressEvent& event)
    {
        if (event._key == GLFW_KEY_W)
            _position.y -= _speed;
        if (event._key == GLFW_KEY_S)
            _position.y += _speed;
        if (event._key == GLFW_KEY_A)
            _position.x += _speed;
        if (event._key == GLFW_KEY_D)
            _position.x -= _speed;

        _shaderProgram->setMatrix4("viewMat", getViewMatrix());
    }

    glm::mat4 Camera2D::getViewMatrix() const
    {
        return glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, -3.0f));
    }

    glm::mat4 Camera2D::getProjectionMatrix(int width, int height) const
    {
        return glm::ortho(0.0f, float(width), float(height), 0.0f, 0.1f, 100.0f);
    }
} // namespace BondEngine