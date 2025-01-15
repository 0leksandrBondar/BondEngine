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

        virtual void draw() const = 0;

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