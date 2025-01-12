#include "ibo.h"

#include <algorithm>

namespace BondEngine
{
    IBO::IBO(IBO&& other) noexcept { *this = std::move(other); }

    IBO& IBO::operator=(IBO&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    IBO::~IBO() { glDeleteBuffers(1, &_id); }

    void IBO::init(const void* vertices, unsigned int size)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void IBO::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }

    void IBO::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace BondEngine