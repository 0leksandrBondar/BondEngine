#pragma once

#include "glad/glad.h"
#include "noncopyable.h"

namespace BondEngine
{
    class IBO : public NonCopyable
    {
    public:
        IBO() = default;
        IBO(IBO&& other) noexcept;
        IBO& operator=(IBO&& other) noexcept;

        ~IBO();

        void init(const void* vertices, unsigned int size);

        void bind() const;
        void unbind() const;

    private:
        GLuint _id{ 0 };
    };
} // namespace BondEngine