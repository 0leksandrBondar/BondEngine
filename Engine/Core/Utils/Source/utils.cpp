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

#include "utils.h"

#include "../../Resources/include/resourcemanager.h"

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

    void initDefaultResources()
    {
        ResourceManager::getInstance()->loadShaderProgram("DefaultShaderProgram",
                                                          "assets/Shaders/vertexSprite.vert",
                                                          "assets/Shaders/fragmentSprite.frag");
    }

    GLFWwindow* createWindow(const int width, const int height, const char* title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }
        return window;
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