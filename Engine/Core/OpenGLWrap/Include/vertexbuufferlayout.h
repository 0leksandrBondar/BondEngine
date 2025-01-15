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

#include "glad/glad.h"

#include <vector>

namespace BondEngine
{

    struct VertexBufferLayoutElement
    {
        GLuint count;
        GLenum type;
        GLboolean normalized;
        size_t size;

        VertexBufferLayoutElement(GLuint c, GLenum t, GLboolean n, unsigned int s)
            : count(c), type(t), normalized(n), size(s)
        {
        }
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout();

        void reserveElements(const unsigned int count);
        void addElementLayoutFloat(const unsigned int count, const bool normalized);

        [[nodiscard]] unsigned int getStride() const;
        [[nodiscard]] const std::vector<VertexBufferLayoutElement>& getElements() const;

    private:
        unsigned int _stride{ 0 };
        std::vector<VertexBufferLayoutElement> _elements;
    };
} // namespace BondEngine