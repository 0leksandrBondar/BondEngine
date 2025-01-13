#pragma once

#include "glm/vec2.hpp"

namespace BondEngine
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        void setRotation(float rotation);

        void setScale(float x, float y);
        void setScale(const glm::vec2& scale);

        void setSize(float width, float height);

        void setPosition(const glm::vec2& position);
        void setPosition(const float x, const float y);

        [[nodiscard]] const float getRotation() const;
        [[nodiscard]] const glm::vec2& getScale() const;
        [[nodiscard]] const glm::vec2& getPosition() const;

    protected:
        float _rotation{};
        glm::vec2 _size{};
        glm::vec2 _scale{};
        glm::vec2 _position{};
    };
} // namespace BondEngine