#include "vbo.h"

#include <algorithm>

namespace BondEngine
{
    VBO::VBO(VBO&& other) noexcept { *this = std::move(other); }

    VBO& VBO::operator=(VBO&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    VBO::~VBO() { glDeleteBuffers(1, &_id); }

    void VBO::init(const void* vertices, unsigned int size)
    {
        glGenBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VBO::update(const void* vertices, unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
    }

    void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

    void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

} // namespace BondEngine