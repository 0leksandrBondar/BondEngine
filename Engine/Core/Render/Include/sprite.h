#pragma once

#include "drawable.h"
#include "noncopyable.h"
#include "transformable.h"

namespace BondEngine
{
    class Texture2D;
    class ShaderProgram;

    class Sprite : public Drawable, public Transformable, public NonCopyable
    {
    public:
        Sprite() = default;

        Sprite(const std::shared_ptr<Texture2D>& texture);

        void draw() const override;


    private:
        std::shared_ptr<Texture2D> _texture;
    };
} // namespace BondEngine