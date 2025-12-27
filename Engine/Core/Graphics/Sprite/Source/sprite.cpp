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
#include "resourcemanager.h"
#include "vertexbuufferlayout.h"
#include "vertices.h"
#include <glad/glad.h>

namespace BondEngine
{

    Sprite::Sprite()
    {
        fillRenderData();
        setupBuffers();
    }

    Sprite::Sprite(ShaderProgram* shader, Texture2D* texture)
    {
        fillRenderData(shader, texture);
        setupBuffers();
    }

    Sprite::Sprite(ShaderProgram* shader, Texture2D* texture, const size_t width,
                   const size_t height)
    {
        fillRenderData(shader, texture);
        setupBuffers();
        setSize(width, height);
    }

    void Sprite::setupBuffers()
    {
        const std::vector<Vertex2D> vertices = { { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
                                                 { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
                                                 { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
                                                 { { 0.0f, 1.0f }, { 0.0f, 1.0f } } };

        _vbo.init(vertices.data(), vertices.size() * sizeof(Vertex2D));

        VertexBufferLayout layout;
        layout.addElementLayoutFloat(2, false);
        layout.addElementLayoutFloat(2, false);
        _renderData.vao.addBuffer(_vbo, layout);

        _ebo.init(_indices, sizeof(_indices));
        _renderData.vao.unbind();
        _ebo.unbind();
    }

    void Sprite::fillRenderData(ShaderProgram* shader, Texture2D* texture)
    {
        if (texture == nullptr && shader == nullptr)
        {
            _renderData.shaderProgram
                = ResourceManager::getInstance()->getShaderProgram("default").get();
            _renderData.texture = ResourceManager::getInstance()->getTexture("default").get();
        }
        else
        {
            _renderData.texture = texture;
            _renderData.shaderProgram = shader;
        }
        _renderData.vertexCount = sizeof(_indices) / sizeof(GLuint);
    }

} // namespace BondEngine
