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

#include "sprite.h"

#include "Texture2D.h"
#include "utils.h"
#include "vertexbuufferlayout.h"
#include "vertices.h"
#include <glad/glad.h>

namespace BondEngine
{

    std::vector<Vertex2D> vertices = { { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
                                       { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
                                       { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
                                       { { 0.0f, 1.0f }, { 0.0f, 1.0f } } };

    const GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

    Sprite::Sprite(const std::shared_ptr<Texture2D>& texture)
    {
        _texture = texture;
        _shaderName = "DefaultShaderProgram";
        _vertexCount = sizeof(indices) / sizeof(GLuint);

        setupBuffers();
    }

    void Sprite::setupBuffers()
    {
        _vbo.init(vertices.data(), vertices.size() * sizeof(Vertex2D));

        VertexBufferLayout layout;
        layout.addElementLayoutFloat(2, false);
        layout.addElementLayoutFloat(2, false);
        _vao.addBuffer(_vbo, layout);

        _ebo.init(indices, sizeof(indices));

        _vao.unbind();
        _ebo.unbind();
    }

} // namespace BondEngine
