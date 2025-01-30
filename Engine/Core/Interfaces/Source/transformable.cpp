#include "transformable.h"

namespace BondEngine
{
    void Transformable::setPosition(const glm::vec2& position)
    {
        _position = position;
        _needsUpdate = true;
    }

    void Transformable::setRotation(const float rotation)
    {
        _rotation = rotation;
        _needsUpdate = true;
    }

    void Transformable::setScale(const glm::vec2& scale)
    {
        _scale = scale;
        _needsUpdate = true;
    }

    void Transformable::move(const float x, const float y)
    {
        _position += glm::vec2(x, y);
        _needsUpdate = true;
    }

    void Transformable::setSize(float width, float height)
    {
        _size = { width, height };
        _needsUpdate = true;
    }

    void Transformable::zoom(float scaleFactor, glm::vec2 targetPos)
    {
        _scale *= scaleFactor;

        const glm::vec2 deltaPosition = (1.0f - scaleFactor) * (targetPos - _position);
        _position += deltaPosition;

        _needsUpdate = true;
    }

    const glm::mat4& Transformable::getTransformMatrix()
    {
        if (_needsUpdate)
            updateTransform();

        return _modelMatrix;
    }

    void Transformable::updateTransform()
    {
        const auto rotationMatrix
            = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f))
              * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.f, 0.f, 1.f))
              * glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

        glm::vec2 size = _isIgnoreSize ? glm::vec2(1.f) : _size;

        auto scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        scaleMatrix = glm::scale(scaleMatrix, glm::vec3(_scale.x, _scale.y, 1.0f));
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(_position, 0.0f));

        _modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        _needsUpdate = false;
    }
} // namespace BondEngine