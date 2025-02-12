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

#include "texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG
#include "stb_image.h"

#include <algorithm>

namespace BondEngine
{
    Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
                         const size_t channels, const GLenum filter, const GLenum wrapMode)
        : _width(width), _height(height)
    {
        initialize(data, channels, filter, wrapMode);
    }

    Texture2D::Texture2D(const std::filesystem::path& path) { loadTexture(path); }

    void Texture2D::loadTexture(const std::filesystem::path& path)
    {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(path.string().c_str(), &_width, &_height, &channels, 0);
        initialize(pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE);
        stbi_image_free(pixels);
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        glDeleteTextures(1, &_id);
        _id = other._id;
        _mode = other._mode;
        _width = other._width;
        _height = other._height;
        return *this;
    }

    void Texture2D::setSmooth(const bool smooth)
    {
        _smooth = smooth;
        bind();

        const GLenum filter = smooth ? GL_LINEAR : GL_NEAREST;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        unbind();
    }

    void Texture2D::initialize(const unsigned char* data, const size_t channels,
                               const GLenum filter, const GLenum wrapMode)
    {
        if (!data)
            throw std::runtime_error("Texture2D: Invalid image data.");

        _format = channels == 4 ? GL_RGBA : GL_RGB;

        glGenTextures(1, &_id);
        bind();

        glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE,
                     data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        unbind();
    }

} // namespace BondEngine
