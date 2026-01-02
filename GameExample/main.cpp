#include "font.h"
#include "freetypelib.h"
#include "resourcemanager.h"
#include "shaderprogram.h"
#include "window.h"

#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include FT_FREETYPE_H

void RenderText(const BondEngine::ShaderProgram* shader, BondEngine::Font* font, std::string text,
                float x, float y, float scale, glm::vec3 color);

unsigned int VAO, VBO;

int main()
{
    const auto window = BondEngine::Window(800, 600, "BondEngine");

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    BondEngine::ResourceManager::getInstance()->loadShaderProgram("default",
                                                                  "Assets/Shaders/Vertex2D.vert",
                                                                  "Assets/Shaders/Fragment2D.frag");
    const auto shader = BondEngine::ResourceManager::getInstance()->getShaderProgram("default");
    const auto face = BondEngine::ResourceManager::getInstance()->getFont("Arial");

    const glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.0f, 600.f);
    shader->activate();
    shader->setMatrix4("projection", projection);

    BondEngine::VAO vao;
    BondEngine::VBO vbo;
    BondEngine::EBO ebo;

    BondEngine::VertexBufferLayout layout;
    layout.addElementLayoutFloat(2, false);
    layout.addElementLayoutFloat(2, false);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (window.isOpen())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RenderText(shader.get(), face.get(), "This is sample text", 25.0f, 25.0f, 1.0f,
                   glm::vec3(0.5, 0.8f, 0.2f));
        RenderText(shader.get(), face.get(), "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
                   glm::vec3(0.3, 0.7f, 0.9f));
        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}

void RenderText(const BondEngine::ShaderProgram* shader, BondEngine::Font* font, std::string text,
                float x, float y, float scale, glm::vec3 color)
{
    shader->activate();
    shader->setVector3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    auto Characters = font->getCharacters();

    for (auto c = text.begin(); c != text.end(); c++)
    {
        BondEngine::Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Texture->getSize().y - ch.Bearing.y) * scale;

        float w = ch.Texture->getSize().x * scale;
        float h = ch.Texture->getSize().y * scale;
        // update VBO for each character
        float vertices[6][4] = { { xpos, ypos + h, 0.0f, 0.0f },    { xpos, ypos, 0.0f, 1.0f },
                                 { xpos + w, ypos, 1.0f, 1.0f },

                                 { xpos, ypos + h, 0.0f, 0.0f },    { xpos + w, ypos, 1.0f, 1.0f },
                                 { xpos + w, ypos + h, 1.0f, 0.0f } };

        ch.Texture->bind();
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                        vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide
                                        // amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// #include "sprite.h"
//
//  #include <window.h>
//
//  #include "inputstate.h"
//  #include "text.h"
//
//  class Window
//  {
//  public:
//      Window(const int width, const int height, const char* title)
//          : _window{ new BondEngine::Window(width, height, title) },
//            _sprite{ new BondEngine::Sprite() },
//            _text{ new BondEngine::Text("Hello OpenGL") }
//      {
//          _sprite->useDefaultTexture();
//          _sprite->setSize(300, 300);
//
//          setupCallbacks();
//      }
//
//      void runMainLoop() const { _window->runMainLoop(); }
//
//  private:
//      void onKeyEvent(BondEngine::KeyState& state, float deltaTime)
//      {
//          auto speed = 200.f;
//
//          if (state.isHold(BondEngine::Key::LShift))
//              speed *= 3;
//          else if (state.isReleased(BondEngine::Key::LShift))
//              speed /= 3;
//
//          if (state.isPressed(BondEngine::Key::Space))
//              _window->getCamera()->setRotation(45);
//
//          if (state.isHold(BondEngine::Key::W))
//              _window->getCamera()->move({ 0.f, -speed * deltaTime });
//          if (state.isHold(BondEngine::Key::A))
//              _window->getCamera()->move({ -speed * deltaTime, 0.f });
//          if (state.isHold(BondEngine::Key::S))
//              _window->getCamera()->move({ 0.f, speed * deltaTime });
//          if (state.isHold(BondEngine::Key::D))
//              _window->getCamera()->move({ speed * deltaTime, 0.f });
//      }
//
//      void onFrameEvent(const float deltaTime) const
//      {
//          //_window->render(_text);
//          _window->render(_sprite);
//      }
//
//      void setupCallbacks()
//      {
//          _window->setKeyPressCallback([this](BondEngine::KeyState& state, float deltaTime)
//                                       { onKeyEvent(state, deltaTime); });
//          _window->setFrameCallback([this](const float deltaTime) { onFrameEvent(deltaTime); });
//      }
//
//  private:
//      BondEngine::Window* _window{ nullptr };
//      BondEngine::Sprite* _sprite{ nullptr };
//      BondEngine::Text* _text{ nullptr };
//  };
//
//  int main()
//  {
//      const auto window = Window(1300, 800, "BondEngine");
//
//      window.runMainLoop();
//      return 0;
//  }
