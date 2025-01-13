#include "vao.h"

#include <algorithm>

namespace BondEngine
{
    VAO::VAO() { glGenVertexArrays(1, &_id); }

    VAO::VAO(VAO&& other) noexcept { *this = std::move(other); }

    VAO& VAO::operator=(VAO&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    VAO::~VAO() { glDeleteVertexArrays(1, &_id); }

    void VAO::addBuffer(const VBO& vertexBuffer, const VertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const auto& elems = layout.getElements();
        for (unsigned int i = 0; i < elems.size(); ++i)
        {
            const auto& elem = elems[i];
            const GLuint currentAttribIndex = _elementsCount + i;
            const GLbyte* offset = nullptr;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, elem.count, elem.type, elem.normalized,
                                  layout.getStride(), offset);
            offset += elem.size;
        }
        _elementsCount += static_cast<unsigned int>(elems.size());
    }

    void VAO::bind() const { glBindVertexArray(_id); }

    void VAO::unbind() const { glBindVertexArray(0); }

} // namespace BondEngine
