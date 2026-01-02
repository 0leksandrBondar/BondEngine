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

#include "singleton.h"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace BondEngine
{
    class Font;
    class Texture2D;
    class ShaderProgram;

    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        ~ResourceManager();

        void loadShaderProgram(const std::string& shaderName,
                               const std::filesystem::path& vertexShaderPath,
                               const std::filesystem::path& fragmentShaderPath);

        void loadTexture2D(const std::string& textureName,
                           const std::filesystem::path& texturePath);

        void loadFont(const std::string& fontName, const std::filesystem::path& fontPath);

        void clearFonts() { _fonts.clear(); }
        void clearTextures() { _textures.clear(); }
        void clearShaderPrograms() { _shaderPrograms.clear(); }

        void clear();

        [[nodiscard]] std::shared_ptr<Font> getFont(const std::string& fontName);
        [[nodiscard]] std::shared_ptr<Texture2D> getTexture(const std::string& shaderName);
        [[nodiscard]] std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderName);

    private:
        std::unordered_map<std::string, std::shared_ptr<Font>> _fonts;
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> _textures;
        std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> _shaderPrograms;
    };
} // namespace BondEngine