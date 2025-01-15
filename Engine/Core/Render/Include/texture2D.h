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

#pragma once

#include <glad/glad.h>

#include "noncopyable.h"

#include <filesystem>

namespace BondEngine
{
    class Texture2D : public NonCopyable
    {
    public:
        Texture2D() = default;

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
    };
} // namespace BondEngine