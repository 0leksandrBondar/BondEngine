#pragma once

#include "glm/mat4x4.hpp"
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
        void setPosition(float x, float y);

        [[nodiscard]] const float getRotation() const;
        [[nodiscard]] const glm::vec2& getSize() const;
        [[nodiscard]] const glm::vec2& getScale() const;
        [[nodiscard]] const glm::vec2& getPosition() const;
        [[nodiscard]] const glm::mat4& getTransformMatrix();

    protected:
        float _rotation{};
        glm::vec2 _size{};
        glm::vec2 _scale{ 1.f };
        glm::vec2 _position{};

    private:
        glm::mat4 _translationMatrix{ 1.0f };
        glm::mat4 _rotationMatrix{ 1.0f };
        glm::mat4 _scaleMatrix{ 1.0f };
        glm::mat4 _transformMatrix{ 1.0f };
        bool _needsUpdate{ true };

        void updateTransform();
    };
} // namespace BondEngine
