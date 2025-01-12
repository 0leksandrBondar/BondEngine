#include "shaderprogram.h"

#include <ostream>

#include "glm/gtc/type_ptr.hpp"

namespace BondEngine
{

    ShaderProgram::ShaderProgram(const std::string& vertexShaderSource,
                                 const std::string& fragmentShaderSource)
    {
        const GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        const GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        createProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept { *this = std::move(other); }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
    {
        if (this == &other)
            return *this; // Self-assignment check

        glDeleteProgram(_programId);

        _programId = other._programId;
        _isCompiled = other._isCompiled;

        other._programId = 0;
        other._isCompiled = false;

        return *this;
    }

    ShaderProgram::~ShaderProgram() { glDeleteProgram(_programId); }

    void ShaderProgram::use() const { glUseProgram(_programId); }

    void ShaderProgram::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
    }

    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE,
                           value_ptr(matrix));
    }

    GLuint ShaderProgram::createShader(const std::string& source, const GLenum shaderType)
    {
        const GLuint shaderID = glCreateShader(shaderType);
        if (shaderID == 0)
        {
            throw std::runtime_error("Failed to create shader!");
        }

        const char* sourcePointer = source.c_str();
        glShaderSource(shaderID, 1, &sourcePointer, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetShaderInfoLog(shaderID, infoLogLength, nullptr, infoLog.data());
            glDeleteShader(shaderID); // Delete the shader on failure
            throw std::runtime_error("Shader compilation error:\n" + infoLog);
        }

        return shaderID;
    }

    void ShaderProgram::createProgram(const GLuint vertexShader, const GLuint fragmentShader)
    {
        _programId = glCreateProgram();
        if (_programId == 0)
        {
            throw std::runtime_error("Failed to create shader program!");
        }

        glAttachShader(_programId, vertexShader);
        glAttachShader(_programId, fragmentShader);
        glLinkProgram(_programId);

        GLint success;
        glGetProgramiv(_programId, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetProgramInfoLog(_programId, infoLogLength, nullptr, infoLog.data());
            glDeleteProgram(_programId); // Delete the program on failure
            throw std::runtime_error("Shader program linking error:\n" + infoLog);
        }

        _isCompiled = true;
    }

} // namespace engine::renderer