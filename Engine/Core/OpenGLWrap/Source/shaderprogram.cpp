// MIT License
//
// Copyright (c) 2024 Oleksandr
//
// Permission is hereby granted, free of charge, to any person obtaining validateProgramLinking copy
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

#include "shaderprogram.h"

#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <iostream>

namespace BondEngine
{

    ShaderProgram::ShaderProgram(const std::filesystem::path& vertexShaderPath,
                                 const std::filesystem::path& fragmentShaderPath)
    {
        const std::string vertexShaderSource = getShaderProgramSourceCode(vertexShaderPath);
        const std::string fragmentShaderSource = getShaderProgramSourceCode(fragmentShaderPath);

        const GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        const GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        createProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    GLuint ShaderProgram::createShader(const std::string& source, GLenum shaderType)
    {
        const GLuint shaderID = glCreateShader(shaderType);
        if (shaderID == 0)
            std::cerr << "ShaderProgram::createShader: Failed to create shader!" << std::endl;

        const char* sourcePointer = source.c_str();

        glShaderSource(shaderID, 1, &sourcePointer, nullptr);
        glCompileShader(shaderID);

        validateShaderCompilation(shaderID);

        return shaderID;
    }

    std::string ShaderProgram::getShaderProgramSourceCode(
        const std::filesystem::path& shaderProgramPath)
    {
        std::ifstream file(shaderProgramPath);
        file.open(shaderProgramPath, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file " + shaderProgramPath.string());

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
    }

    void ShaderProgram::validateProgramLinking(GLuint shaderID) const
    {
        GLint success;
        glGetProgramiv(_id, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetProgramInfoLog(_id, infoLogLength, nullptr, infoLog.data());
            glDeleteProgram(_id);
            std::cerr << "ShaderProgram::сheckProgramLink: " + infoLog << std::endl;
        }
    }

    void ShaderProgram::validateShaderCompilation(const GLuint shaderID) const
    {
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint infoLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetShaderInfoLog(shaderID, infoLogLength, nullptr, infoLog.data());
            glDeleteShader(shaderID);

            std::cerr << "ShaderProgram::сheckShaderCompilation: " + infoLog << std::endl;
        }
    }

    void ShaderProgram::createProgram(const GLuint vertexShader, const GLuint fragmentShader)
    {
        _id = glCreateProgram();
        if (_id == 0)
            std::cerr << "ShaderProgram::createProgram: Failed to create program!" << std::endl;

        glAttachShader(_id, vertexShader);
        glAttachShader(_id, fragmentShader);
        glLinkProgram(_id);

        validateProgramLinking(_id);

        _isCompiled = true;
    }

} // namespace BondEngine
