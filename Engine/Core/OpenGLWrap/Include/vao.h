#pragma once

#include "glad/glad.h"
#include "noncopyable.h"
#include "vertexbuufferlayout.h"

#include "vbo.h"

namespace BondEngine
{
    class VAO final : public NonCopyable
    {
    public:
        VAO();
        VAO(VAO&& other) noexcept;
        VAO& operator=(VAO&& other) noexcept;
        ~VAO();

        void addBuffer(const VBO& vertexBuffer, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;

    private:
        GLuint _id{ 0 };
        unsigned int _elementsCount{ 0 };
    };

} // namespace BondEngine