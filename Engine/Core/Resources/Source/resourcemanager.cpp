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

#include "resourcemanager.h"

#include "shaderprogram.h"
#include "texture2D.h"
#include "utils.h"

namespace BondEngine
{
    void ResourceManager::loadShaderProgram(const std::string& shaderName,
                                            const std::filesystem::path& vertexShaderPath,
                                            const std::filesystem::path& fragmentShaderPath)
    {
        _shaderPrograms.emplace(shaderName, std::make_shared<ShaderProgram>(vertexShaderPath,
                                                                            fragmentShaderPath));
    }

    void ResourceManager::loadTexture2D(const std::string& textureName,
                                        const std::filesystem::path& texturePath)
    {
        auto texture = std::make_shared<Texture2D>(texturePath);
        _textures.emplace(textureName, texture);
    }

    std::shared_ptr<Texture2D> ResourceManager::getTexture(const std::string& shaderName)
    {
        const auto it = _textures.find(shaderName);
        if (it != _textures.cend())
            return it->second;

        return nullptr;
    }

    std::shared_ptr<ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
    {
        const auto it = _shaderPrograms.find(shaderName);
        if (it != _shaderPrograms.cend())
            return it->second;

        return nullptr;
    }

} // namespace BondEngine