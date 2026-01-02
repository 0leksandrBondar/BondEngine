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
#include "font.h"
#include "resourcemanager.h"
#include "vertices.h"

namespace BondEngine
{

    class Glyph final : public Drawable
    {
    public:
        explicit Glyph(const Character& character)
        {
            _renderData.texture = character.Texture;
            _renderData.shaderProgram
                = ResourceManager::getInstance()->getShaderProgram("default").get();
            _renderData.color = glm::vec4(1.f);

            setupMesh(character);
        }

    private:
        void setupMesh(const Character& ch)
        {
            const float w = static_cast<float>(ch.Texture->getSize().x);
            const float h = static_cast<float>(ch.Texture->getSize().y);

            const std::vector<Vertex2D> vertices
                = { { { 0.f, h }, { 0.f, 0.f } }, { { 0.f, 0.f }, { 0.f, 1.f } },
                    { { w, 0.f }, { 1.f, 1.f } },

                    { { 0.f, h }, { 0.f, 0.f } }, { { w, 0.f }, { 1.f, 1.f } },
                    { { w, h }, { 1.f, 0.f } } };

            _renderData.vertexCount = static_cast<unsigned>(vertices.size());

            VertexBufferLayout layout;
            layout.reserveElements(2);
            layout.addElementLayoutFloat(2, false); // position
            layout.addElementLayoutFloat(2, false); // texCoords

            _renderData.vao.bind();
            _vbo.init(vertices.data(), vertices.size() * sizeof(Vertex2D));
            _renderData.vao.addBuffer(_vbo, layout);
            _renderData.vao.unbind();

            setSize(w, h);
            ignoreSize(false);
        }
    };

    class Text final : public Drawable
    {
    public:
        Text() = default;
        explicit Text(const char* text);

        [[nodiscard]] Font& getFont() { return _font; }

    private:
        void setupBuffers();

    private:
        Font _font;
    };

} // namespace BondEngine