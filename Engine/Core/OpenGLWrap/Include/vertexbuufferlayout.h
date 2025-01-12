#pragma once

#include "glad/glad.h"

#include <vector>

namespace BondEngine
{

    struct VertexBufferLayoutElement
    {
        GLuint count;
        GLenum type;
        GLboolean normalized;
        size_t size;

        VertexBufferLayoutElement(GLuint c, GLenum t, GLboolean n, unsigned int s)
            : count(c), type(t), normalized(n), size(s)
        {
        }
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout();

        void reserveElements(const unsigned int count);
        void addElementLayoutFloat(const unsigned int count, const bool normalized);

        [[nodiscard]] unsigned int getStride() const;
        [[nodiscard]] const std::vector<VertexBufferLayoutElement>& getElements() const;

    private:
        unsigned int _stride{ 0 };
        std::vector<VertexBufferLayoutElement> _elements;
    };
} // namespace BondEngine