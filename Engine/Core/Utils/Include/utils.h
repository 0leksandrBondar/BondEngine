#pragma once

#include <filesystem>

namespace BondEngine::utils
{
    int initGLAD();
    void initGLFW();
    void initDefaultResources();

    std::string getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath);
} // namespace BondEngine::utils
