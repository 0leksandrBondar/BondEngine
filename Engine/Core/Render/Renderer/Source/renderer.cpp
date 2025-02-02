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

namespace BondEngine
{

    void Renderer::render(Drawable* item)
    {
        _shaderProgram
            = ResourceManager::getInstance()->getShaderProgram(item->getShaderName()).get();
        _shaderProgram->use();

        updateMatrix(item);

        item->getVAO().bind();

        if (item->getTexture() != nullptr)
            item->getTexture()->bind();

        glDrawElements(GL_TRIANGLES, item->getVertexCount(), GL_UNSIGNED_INT, nullptr);

        if (item->getTexture() != nullptr)
            item->getTexture()->unbind();

        item->getVAO().unbind();
    }

    std::string Renderer::getGPUBrand()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }

    void Renderer::updateMatrix(Drawable* item) const
    {
        _shaderProgram->setMatrix4("projectionMat", _projectionMatrix);
        _shaderProgram->setMatrix4("modelMat", item->getTransformMatrix());
        _shaderProgram->setMatrix4("viewMat", _camera->getTransformMatrix());
    }

} // namespace BondEngine
