#include "transformable.h"

#include "glm/gtc/matrix_transform.hpp"

namespace BondEngine
{
    void Transformable::setPosition(const glm::vec2& position)
    {
        _position = position;
        _translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(_position, 0.0f));
        _needsUpdate = true;
    }

    void Transformable::setPosition(float x, float y) { setPosition(glm::vec2(x, y)); }

    void Transformable::setRotation(float rotation)
    {
        _rotation = rotation;

        _rotationMatrix
            = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f))
              * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.f, 0.f, 1.f))
              * glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

        _needsUpdate = true;
    }

    void Transformable::setScale(float x, float y) { setScale(glm::vec2(x, y)); }

    void Transformable::setScale(const glm::vec2& scale)
    {
        _scale = scale;
        _scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(_size * _scale, 1.0f));
        _needsUpdate = true;
    }

    void Transformable::setSize(float width, float height)
    {
        _size = { width, height };
        _scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(_size * _scale, 1.0f));
        _needsUpdate = true;
    }

    const float Transformable::getRotation() const { return _rotation; }

    const glm::vec2& Transformable::getSize() const { return _size; }

    const glm::vec2& Transformable::getScale() const { return _scale; }

    const glm::vec2& Transformable::getPosition() const { return _position; }

    const glm::mat4& Transformable::getTransformMatrix()
    {
        if (_needsUpdate)
        {
            updateTransform();
        }
        return _transformMatrix;
    }

    void Transformable::updateTransform()
    {
        _transformMatrix = _translationMatrix * _rotationMatrix * _scaleMatrix;
        _needsUpdate = false;
    }
} // namespace BondEngine