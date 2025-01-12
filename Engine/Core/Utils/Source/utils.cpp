#include "utils.h"

#include <iostream>
#include <opengl.h>
#include <ostream>

#include <fstream>

namespace BondEngine::utils
{

    void initGLFW()
    {
        if (!glfwInit())
            std::cerr << "Failed to initialize GLFW" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    std::string getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath)
    {
        std::ifstream file(shaderProgramPath);
        file.open(shaderProgramPath, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file " + shaderProgramPath.string());

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    int initGLAD() { return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); }
} // namespace BondEngine::utils