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
#include "shaderprogram.h"
#include "utils.h"
#include "vertexbuufferlayout.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace BondEngine
{
    constexpr GLfloat vertexCoords[] = {
        0.0f, 0.f, 0.0f, 1.f, 1.0f, 1.f, 1.0f, 0.f,
    };

    constexpr GLfloat textureCoords[] = {
        0.0f, 0.f, 0.0f, 1.f, 1.0f, 1.f, 1.0f, 0.f,
    };

    const GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

    Sprite::Sprite(const std::shared_ptr<Texture2D>& texture) : _texture{ texture }
    {
        const glm::mat4 projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -100.f, 100.f);

        _shaderProgram->use();
        _shaderProgram->setInt("tex", 0);
        _shaderProgram->setMatrix4("projectionMat", projection);

        setupBuffers();
    }

    void Sprite::draw()
    {
        _shaderProgram->use();
        _shaderProgram->setMatrix4("modelMat", calculateModelMatrix());

        _vao.bind();

        glActiveTexture(GL_TEXTURE0);
        _texture->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        _vao.unbind();
    }

    void Sprite::setupBuffers()
    {
        _vbo.init(vertexCoords, sizeof(vertexCoords));
        VertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.addElementLayoutFloat(2, false);
        _vao.addBuffer(_vbo, vertexCoordsLayout);

        _tvbo.init(textureCoords, sizeof(textureCoords));
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2, false);
        _vao.addBuffer(_tvbo, textureCoordsLayout);

        _ibo.init(indices, sizeof(indices));
        _vao.unbind();
        _ibo.unbind();
    }

    glm::mat4 Sprite::calculateModelMatrix() const
    {
        auto model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(_position, 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
        model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));
        return glm::scale(model, glm::vec3(_size, 1.0f));
    }

} // namespace BondEngine