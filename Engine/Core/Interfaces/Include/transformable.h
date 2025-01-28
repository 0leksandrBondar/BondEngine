#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace BondEngine
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        void setPosition(float x, float y);
        void setPosition(const glm::vec2& position);

        void setRotation(float rotation);

        void setScale(float x, float y);
        void setScale(const glm::vec2& scale);

        void move(float x, float y);
        void setSize(float width, float height);

        void zoom(float scaleFactor, glm::vec2 targetPos);

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
