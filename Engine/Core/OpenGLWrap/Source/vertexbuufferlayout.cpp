#include "vertexbuufferlayout.h"

namespace BondEngine
{
    VertexBufferLayout::VertexBufferLayout() {}

    void VertexBufferLayout::reserveElements(const unsigned int count) { _elements.reserve(count); }

    void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
    {
        VertexBufferLayoutElement a(static_cast<GLint>(count), GL_FLOAT, normalized,
                                    count * sizeof(GLfloat));
        _elements.push_back(a);
        _stride += static_cast<unsigned int>(_elements.back().size);
    }

    unsigned int VertexBufferLayout::getStride() const { return _stride; }

    const std::vector<VertexBufferLayoutElement>& VertexBufferLayout::getElements() const
    {
        return _elements;
    }
} // namespace BondEngine