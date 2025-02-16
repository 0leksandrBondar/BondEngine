#pragma once

#include "noncopyable.h"

#include <string>
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

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include <filesystem>

namespace BondEngine
{
    class ShaderProgram final
    {
    public:
        ShaderProgram() = default;
        ShaderProgram(const ShaderProgram& other) = delete;

        ShaderProgram(const std::filesystem::path& vertexShaderPath,
                      const std::filesystem::path& fragmentShaderPath);

        ~ShaderProgram() { glDeleteProgram(_id); }

        void activate() const { glUseProgram(_id); }

        void setBool(const std::string& name, bool value) const;
        void setMatrix4(const std::string& name, const glm::mat4& matrix) const;

        [[nodiscard]] bool isCompiled() const { return _isCompiled; }

    private:
        void validateProgramLinking(GLuint shaderID) const;
        void validateShaderCompilation(GLuint shaderID) const;
        void createProgram(GLuint vertexShader, GLuint fragmentShader);
        GLuint createShader(const std::string& source, GLenum shaderType);

        std::string getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath);

    private:
        GLuint _id;
        bool _isCompiled{ false };
    };

} // namespace BondEngine
