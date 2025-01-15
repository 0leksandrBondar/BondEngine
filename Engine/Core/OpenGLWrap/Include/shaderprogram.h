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

namespace BondEngine
{
    class ShaderProgram final : public NonCopyable
    {
    public:
        ShaderProgram(const std::string& vertexShaderSource,
                      const std::string& fragmentShaderSource);
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;
        ~ShaderProgram() override;

        void use() const;
        void setInt(const std::string& name, int value) const;
        void setMatrix4(const std::string& name, const glm::mat4& matrix) const;

        [[nodiscard]] bool isCompiled() const noexcept { return _isCompiled; }

    private:
        GLuint createShader(const std::string& source, GLenum shaderType);
        void createProgram(GLuint vertexShader, GLuint fragmentShader);

    private:
        GLuint _programId{ 0 };
        bool _isCompiled{ false };
    };

} // namespace BondEngine