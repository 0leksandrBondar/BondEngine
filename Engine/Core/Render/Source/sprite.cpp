#include "sprite.h"

#include "Texture2D.h"
#include "shaderprogram.h"
#include "utils.h"
#include "vertexbuufferlayout.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace BondEngine
{

    Sprite::Sprite(const std::shared_ptr<Texture2D>& texture) : _texture{ texture }
    {
        // clang-format off

        // 1--2
        // | /|
        // 0-3

        // X Y

         constexpr GLfloat vertexCoords[] =
        {
            0.0f,  0.f,
            0.0f,  1.f,
            1.0f,  1.f,

            1.0f,  0.f,
        };

         constexpr GLfloat textureCoords[] =
        {
            // U V
            0.0f,  0.f,
            0.0f,  1.f,
            1.0f,  1.f,
            1.0f,  0.f,
        };

        const GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

        // clang-format on

        initDefaultShaderProgram();
        const glm::mat4 projection = glm::ortho(0.f, 940.f, 800.f, 0.f, -100.f, 100.f);

        _shaderProgram->use();
        _shaderProgram->setInt("tex", 0);
        _shaderProgram->setMatrix4("projectionMat", projection);

        _vbo.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.addElementLayoutFloat(2, false);
        _vao.addBuffer(_vbo, vertexCoordsLayout);

        _tvbo.init(textureCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2, false);
        _vao.addBuffer(_tvbo, textureCoordsLayout);

        _ibo.init(indices, 6 * sizeof(GLfloat));

        _vao.unbind();
        _ibo.unbind();
    }

    void Sprite::render() const
    {
        _shaderProgram->use();
        auto model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(_position, 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
        model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));
        model = glm::scale(model, glm::vec3(_size, 1.0f));

        _vao.bind();
        _shaderProgram->setMatrix4("modelMat", model);

        glActiveTexture(GL_TEXTURE0);
        _texture->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        _vao.unbind();
    }

    void Sprite::initDefaultShaderProgram()
    {
        _shaderProgram
            = std::make_shared<ShaderProgram>(utils::getShaderProgramSourceCode(_vertexShaderPath),
                                              utils::getShaderProgramSourceCode(
                                                  _fragmentShaderPath));
    }

} // namespace BondEngine