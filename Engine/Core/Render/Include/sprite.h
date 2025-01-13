#pragma once

#include "noncopyable.h"
#include "transformable.h"

#include "ibo.h"
#include "vao.h"
#include "vbo.h"

#include <filesystem>
#include <memory>

namespace BondEngine
{
    class Texture2D;
    class ShaderProgram;

    class Sprite : public Transformable, public NonCopyable
    {
    public:
        Sprite() = default;

        Sprite(const std::shared_ptr<Texture2D>& texture);

        void render() const;

    private:
        void initDefaultShaderProgram();

    private:
        std::shared_ptr<Texture2D> _texture;
        std::shared_ptr<ShaderProgram> _shaderProgram;

        const std::filesystem::path _vertexShaderPath{ "assets/Shaders/vertexSprite.vert" };
        const std::filesystem::path _fragmentShaderPath{ "assets/Shaders/fragmentSprite.frag" };

        VAO _vao{};
        IBO _ibo{};
        VBO _vbo{};
        VBO _tvbo{};
    };
} // namespace BondEngine