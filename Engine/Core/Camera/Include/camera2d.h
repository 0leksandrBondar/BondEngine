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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BondEngine
{
    class Camera2D
    {
    public:
        Camera2D(float viewportWidth, float viewportHeight);

        // Position
        void setPosition(const glm::vec2& pos);
        void move(const glm::vec2& delta);

        // Rotation (degrees)
        void setRotation(float degrees);
        void rotate(float delta);

        // Zoom
        void setZoom(float zoom);
        void zoom(float factor);

        // Viewport
        void setViewport(float width, float height);

        // Matrix
        const glm::mat4& getViewMatrix() const;

        // Getters
        glm::vec2 getPosition() const { return _position; }
        float getRotation() const { return _rotation; }
        float getZoom() const { return _zoom; }

    private:
        void updateMatrix() const;

        mutable glm::mat4 _viewMatrix{1.0f};
        mutable bool _dirty{true};

        glm::vec2 _position{0.f, 0.f};
        float _rotation{0.f};   // degrees
        float _zoom{1.f};

        glm::vec2 _viewport{1.f, 1.f};
    };
}
