#pragma once

#include "singleton.h"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace BondEngine
{
    class Texture2D;
    class ShaderProgram;

    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        void loadShaderProgram(const std::string& shaderName,
                               const std::filesystem::path& vertexShaderPath,
                               const std::filesystem::path& fragmentShaderPath);

        void loadTexture2D(const std::string& textureName,
                           const std::filesystem::path& texturePath);

        [[nodiscard]] std::shared_ptr<Texture2D> getTexture(const std::string& shaderName);
        [[nodiscard]] std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderName);

    private:
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> _textures;
        std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> _shaderPrograms;
    };
} // namespace BondEngine