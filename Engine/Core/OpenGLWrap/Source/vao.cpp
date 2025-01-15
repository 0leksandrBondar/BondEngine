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

#include "vao.h"

#include <algorithm>

namespace BondEngine
{
    VAO::VAO() { glGenVertexArrays(1, &_id); }

    VAO::VAO(VAO&& other) noexcept { *this = std::move(other); }

    VAO& VAO::operator=(VAO&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    VAO::~VAO() { glDeleteVertexArrays(1, &_id); }

    void VAO::addBuffer(const VBO& vertexBuffer, const VertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const auto& elems = layout.getElements();
        for (unsigned int i = 0; i < elems.size(); ++i)
        {
            const auto& elem = elems[i];
            const GLuint currentAttribIndex = _elementsCount + i;
            const GLbyte* offset = nullptr;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, elem.count, elem.type, elem.normalized,
                                  layout.getStride(), offset);
            offset += elem.size;
        }
        _elementsCount += static_cast<unsigned int>(elems.size());
    }

    void VAO::bind() const { glBindVertexArray(_id); }

    void VAO::unbind() const { glBindVertexArray(0); }

} // namespace BondEngine
