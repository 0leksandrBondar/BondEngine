#include "EBO.h"
#include "renderer.h"
#include "shaderprogram.h"
#include "sprite.h"
#include "texture2D.h"
#include "vao.h"
#include "vertices.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <window.h>

std::vector<Vertex3D> cubeVertices = { { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
                                       { { 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
                                       { { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f } },
                                       { { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f } },
                                       { { -0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 1.0f } },
                                       { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 1.0f } },
                                       { { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f } },
                                       { { -0.5f, 0.5f, 0.5f }, { 0.2f, 0.3f, 0.8f } } };

unsigned int indices[] = { 0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
                           4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4 };

int main()
{
    const auto window = new BondEngine::Window(1300, 800, "BondEngine");
    glEnable(GL_DEPTH_TEST);

    BondEngine::VAO vao;
    BondEngine::VBO vbo;
    BondEngine::EBO ebo;

    vbo.init(cubeVertices.data(), cubeVertices.size() * sizeof(Vertex3D));
    BondEngine::VertexBufferLayout layout;
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(3, false);
    vao.addBuffer(vbo, layout);
    ebo.init(indices, sizeof(indices));
    vao.unbind();
    ebo.unbind();

    const auto shaderProgram = new BondEngine::ShaderProgram("Assets/Shaders/Vertex3D.vert",
                                                             "Assets/Shaders/Fragment3D.frag");
    const auto shaderProgram2 = new BondEngine::ShaderProgram("Assets/Shaders/Vertex2D.vert",
                                                              "Assets/Shaders/Fragment2D.frag");

    auto texture = new BondEngine::Texture2D("Assets/Textures/DefaultTexture.png");
    auto sprite = new BondEngine::Sprite(shaderProgram2, texture);
    auto renderer = new BondEngine::Renderer(nullptr);

    sprite->setSize(300, 300);

    shaderProgram->activate();

    glm::mat4 view = glm::lookAt(glm::vec3(1.5f, 1.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1300.f / 800.f, 0.1f, 100.0f);

    shaderProgram->setMatrix4("view", view);
    shaderProgram->setMatrix4("projection", projection);

    while (window->isOpen())
    {
        window->clear(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram->activate();

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        shaderProgram->setMatrix4("model", model);

        texture->bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        renderer->render(sprite);

        window->swapBuffers();
        window->pollEvents();
    }

    glfwTerminate();
    return 0;
}
