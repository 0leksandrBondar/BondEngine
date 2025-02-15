#include "shaderprogram.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <window.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                     0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,
                     -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 1.0f,
                     0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, -0.5f, 0.5f,  0.5f,  0.2f, 0.3f, 0.8f };

unsigned int indices[] = { 0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
                           4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4 };

int main()
{
    const auto window = new BondEngine::Window(SCR_WIDTH, SCR_HEIGHT, "BondEngine");
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const auto shaderProgram = new BondEngine::ShaderProgram("Assets/Shaders/Vertex3d.vert",
                                                             "Assets/Shaders/Fragment3D.frag");

    while (window->isOpen())
    {
        window->clear(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram->activate();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::lookAt(glm::vec3(1.5f, 1.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                                     glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        shaderProgram->setMatrix4("model", model);
        shaderProgram->setMatrix4("view", view);
        shaderProgram->setMatrix4("projection", projection);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        window->swapBuffers();
        window->pollEvents();
    }

    glfwTerminate();
    return 0;
}
