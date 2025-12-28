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

#include "window.h"
#include "Camera2D.h"

#include "camera2d.h"

namespace BondEngine
{
    Camera2D::Camera2D(float viewportWidth, float viewportHeight)
        : _viewport(viewportWidth, viewportHeight)
    {
    }

    void Camera2D::setPosition(const glm::vec2& pos)
    {
        _position = pos;
        _dirty = true;
    }

    void Camera2D::move(const glm::vec2& delta)
    {
        _position += delta;
        _dirty = true;
    }

    void Camera2D::setRotation(float degrees)
    {
        _rotation = degrees;
        _dirty = true;
    }

    void Camera2D::rotate(float delta)
    {
        _rotation += delta;
        _dirty = true;
    }

    void Camera2D::setZoom(float zoom)
    {
        _zoom = zoom;
        _dirty = true;
    }

    void Camera2D::zoom(float factor)
    {
        _zoom *= factor;
        _dirty = true;
    }

    void Camera2D::setViewport(float width, float height)
    {
        _viewport = {width, height};
        _dirty = true;
    }

    const glm::mat4& Camera2D::getViewMatrix() const
    {
        if (_dirty)
            updateMatrix();
        return _viewMatrix;
    }

    void Camera2D::updateMatrix() const
    {

        glm::mat4 view(1.0f);

        // 1️⃣ move world to screen center
        view = glm::translate(view,
            glm::vec3(_viewport.x * 0.5f, _viewport.y * 0.5f, 0.f));

        // 2️⃣ rotate world opposite to camera
        view = glm::rotate(view,
            glm::radians(-_rotation),
            glm::vec3(0.f, 0.f, 1.f));

        // 3️⃣ zoom
        view = glm::scale(view,
            glm::vec3(_zoom, _zoom, 1.f));

        // 4️⃣ move world opposite to camera position
        view = glm::translate(view,
            glm::vec3(-_position, 0.f));

        _viewMatrix = view;
        _dirty = false;
    }
}
