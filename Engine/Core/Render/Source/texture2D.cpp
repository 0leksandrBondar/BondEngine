#include "texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG
#include "stb_image.h"

#include <algorithm>

namespace BondEngine
{
    Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
                         unsigned int channels, const GLenum filter, const GLenum wrapMode)
        : _width(width), _height(height)
    {
        intialize(width, height, data, channels, filter, wrapMode);
    }

    Texture2D::Texture2D(const std::filesystem::path& path) { loadTexture(path); }

    void Texture2D::loadTexture(const std::filesystem::path& path)
    {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(path.string().c_str(), &_width, &_height, &channels, 0);
        intialize(_width, _height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE);
        stbi_image_free(pixels);
    }

    Texture2D::Texture2D(Texture2D&& other) noexcept { *this = std::move(other); }

    Texture2D::~Texture2D() { glDeleteTextures(1, &_id); }

    Texture2D& Texture2D::operator=(const Texture2D&& other) noexcept
    {
        glDeleteTextures(1, &_id);
        _id = other._id;
        _mode = other._mode;
        _width = other._width;
        _height = other._height;
        return *this;
    }

    void Texture2D::bind() const { glBindTexture(GL_TEXTURE_2D, _id); }
    void Texture2D::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    void Texture2D::intialize(const GLuint width, const GLuint height, const unsigned char* data,
                              unsigned int channels, const GLenum filter, const GLenum wrapMode)
    {
        switch (channels)
        {
        case 4:
            _mode = GL_RGBA;
            break;
        case 3:
            _mode = GL_RGB;
            break;
        default:
            _mode = GL_RGB;
        }

        glGenTextures(1, &_id);
        bind();

        glTexImage2D(GL_TEXTURE_2D, 0, _mode, _width, _height, 0, _mode, GL_UNSIGNED_BYTE, data);
        glActiveTexture(GL_TEXTURE0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, wrapMode);
        glGenerateMipmap(GL_TEXTURE_2D);

        unbind();
    }

} // namespace BondEngine
