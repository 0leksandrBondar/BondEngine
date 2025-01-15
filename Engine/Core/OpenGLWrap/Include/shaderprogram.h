#pragma once

#include "noncopyable.h"

#include <string>

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