#pragma once

#include "glad/glad.h"
#include "noncopyable.h"

namespace BondEngine
{
    class VBO final : public NonCopyable
    {
    public:
        VBO() = default;
        VBO(VBO&& other) noexcept;
        VBO& operator=(VBO&& other) noexcept;

        ~VBO();

        void init(const void* vertices, unsigned int size);
        void update(const void* vertices, unsigned int size) const;

        void bind() const;
        void unbind() const;

    private:
        GLuint _id{ 0 };
    };

} // namespace BondEngine