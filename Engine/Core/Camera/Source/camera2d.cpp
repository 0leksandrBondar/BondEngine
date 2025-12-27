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

#include <iostream>

namespace BondEngine
{

    Camera2D::Camera2D() { ignoreSize(true); }

    void Camera2D::move(const float x, const float y)
    {
        Transformable::move(x, y);
        _viewNeedsUpdate = true;
    }

    void Camera2D::setPosition(const glm::vec2& pos)
    {
        Transformable::setPosition(pos);
        _viewNeedsUpdate = true;
    }

    void Camera2D::setScale(const glm::vec2& scale)
    {
        Transformable::setScale(scale);
        _viewNeedsUpdate = true;
    }

    void Camera2D::zoom(const float factor, const glm::vec2 target)
    {
        Transformable::zoom(factor, target);
        _viewNeedsUpdate = true;
    }

    void Camera2D::update() {}

    const glm::mat4& Camera2D::getViewMatrix()
    {
        if (_viewNeedsUpdate)
        {
            const glm::mat4& model = getTransformMatrix();
            _viewMatrix = glm::inverse(model);

            _viewNeedsUpdate = false;
        }

        return _viewMatrix;
    }


} // namespace BondEngine
