#pragma once

#include <glad/glad.h>

#include "noncopyable.h"

#include <filesystem>

namespace BondEngine
{
    class Texture2D : public NonCopyable
    {
    public:
        Texture2D();

        Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
                  unsigned int channels = 4, const GLenum filter = GL_LINEAR,
                  const GLenum wrapMode = GL_CLAMP_TO_EDGE);
        explicit Texture2D(const std::filesystem::path& path);

        Texture2D(Texture2D&& other) noexcept;

        ~Texture2D();

        Texture2D& operator=(const Texture2D&& other) noexcept;

        void bind() const;
        void unbind() const;

    private:
        void loadTexture(const std::filesystem::path& path);
        void intialize(const GLuint width, const GLuint height, const unsigned char* data,
                       unsigned int channels = 4, const GLenum filter = GL_LINEAR,
                       const GLenum wrapMode = GL_CLAMP_TO_EDGE);

    private:
        GLenum _mode;
        GLuint _id{ 0 };
        int channels{ 0 };
        int _width{ 0 }, _height{ 0 };

        const std::filesystem::path _defaultTexturePath{ "assets/Textures/DefaultTexture.png" };
    };
} // namespace BondEngine