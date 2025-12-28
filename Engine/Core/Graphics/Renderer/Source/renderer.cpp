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

#include "renderer.h"

#include "resourcemanager.h"
#include "shaderprogram.h"

#include "window.h"

namespace BondEngine
{
    Renderer::Renderer(Camera2D* camera, Window* window) : _window(window), _camera(camera)
    {
        _projectionMatrix = glm::ortho(0.f, _window->getWindowSize().x, _window->getWindowSize().y,
                                       0.f, -100.f, 100.f);
    }

    void Renderer::render(Drawable* item) const
    {
        const RenderData& data = item->getRenderData();

        data.shaderProgram->activate();

        updateMatrix(data.shaderProgram, item->getTransformMatrix());

        data.vao.bind();

        data.shaderProgram->setVector4("spriteColor", data.color);
        data.shaderProgram->setBool("useTexture", data.texture != nullptr);

        if (item->getTexture() != nullptr)
            item->getTexture()->bind();

        glDrawElements(GL_TRIANGLES, data.vertexCount, GL_UNSIGNED_INT, nullptr);

        if (item->getTexture() != nullptr)
            item->getTexture()->unbind();

        data.vao.unbind();
    }

    std::string Renderer::getGPUBrand()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }

    void Renderer::updateMatrix(const ShaderProgram* shader, const glm::mat4& modelMat) const
    {
        shader->setMatrix4("modelMat", modelMat);
        shader->setMatrix4("projectionMat", _projectionMatrix);
        shader->setMatrix4("viewMat", _camera->getViewMatrix());
    }

} // namespace BondEngine
