#include "transformable.h"

namespace BondEngine
{
    void Transformable::setPosition(const glm::vec2& position) { _position = position; }

    void Transformable::setPosition(const float x, const float y) { _position = glm::vec2(x, y); }

    const float Transformable::getRotation() const { return _rotation; }

    const glm::vec2& Transformable::getSize() const { return _size; }

    const glm::vec2& Transformable::getScale() const { return _scale; }

    const glm::vec2& Transformable::getPosition() const { return _position; }

    void Transformable::setRotation(float rotation) { _rotation = rotation; }

    void Transformable::setScale(float x, float y) { _scale = glm::vec2(x, y); }

    void Transformable::setScale(const glm::vec2& scale) { _scale = scale; }

    void Transformable::setSize(float width, float height) { _size = glm::vec2(width, height); }
} // namespace BondEngine