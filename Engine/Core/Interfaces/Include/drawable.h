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

#include "ibo.h"
#include "vao.h"
#include "vbo.h"

#include <memory>

namespace BondEngine
{

    class ShaderProgram;

    class Drawable
    {
    public:
        Drawable();
        virtual ~Drawable() = default;

        virtual void draw() = 0;

        void setShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram);

    private:
        void initDefaultShaderProgram();

    protected:
        VAO _vao{};
        IBO _ibo{};
        VBO _vbo{};
        VBO _tvbo{};

        std::shared_ptr<ShaderProgram> _shaderProgram;
    };
} // namespace BondEngine