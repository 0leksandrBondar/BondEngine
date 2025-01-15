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
        auto shaderProgram
            = std::make_shared<ShaderProgram>(utils::getShaderProgramSourceCode(vertexShaderPath),
                                              utils::getShaderProgramSourceCode(
                                                  fragmentShaderPath));
        _shaderPrograms.emplace(shaderName, shaderProgram);
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