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

#include "drawable.h"
#include "noncopyable.h"

namespace BondEngine
{

    class Sprite final : public Drawable, public NonCopyable
    {
    public:
        Sprite();
        Sprite(ShaderProgram* shader, Texture2D* texture);
        Sprite(ShaderProgram* shader, Texture2D* texture, size_t width, size_t height);

        void setColor(glm::vec4 color);
        void setTexture(Texture2D* texture);

        // debug text remove it
        void useDefaultTexture();

    private:
        void setupBuffers();
        void fillRenderData(ShaderProgram* shader = nullptr, Texture2D* texture = nullptr);

    private:
        static constexpr GLuint _indices[] = { 0, 1, 2, 2, 3, 0 };
    };
} // namespace BondEngine
