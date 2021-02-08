#include "Game.h"

#define PAPAYA_MAIN
#include "EntryPoint.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"
#include "main/events/EventQueue.h"

#include "main/core/Log.h"
#include "main/core/Platform.h"

#include "main/utils/String.h"

#include "platform/OpenGL/OpenGLLoader.h"

namespace Papaya
{

Game::Game() {
  m_Window = Window::Create();
}

Game::~Game() {

}

void Game::Run() {
  m_Window->Show();

  const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
  const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
    // first triangle
    -0.9f, -0.5f, 0.0f,  // left 
    -0.0f, -0.5f, 0.0f,  // right
    -0.45f, 0.5f, 0.0f,  // top 
    // second triangle
     0.0f, -0.5f, 0.0f,  // left
     0.9f, -0.5f, 0.0f,  // right
     0.45f, 0.5f, 0.0f   // top 
  };

  uint32_t indices[] = {
    0, 1, 2,
    3, 4, 5
  };

  Ref<Buffer> vertexBuffer;
  Ref<Buffer> indexBuffer;
  GLuint VAO;

  glGenVertexArrays(1, &VAO);
  indexBuffer = Buffer::Create(indices, sizeof(indices), BufferType::Index);
  vertexBuffer = Buffer::Create(vertices, sizeof(vertices), BufferType::Vertex);

  glBindVertexArray(VAO);
  vertexBuffer->Bind();
  indexBuffer->Bind();
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  while (m_Running) {
    Platform::OnUpdate(); // Poll Events

    while (!EventQueue::Empty()) // Process Events
    {
      Scope<Event> e(EventQueue::PopEvent());
      PAPAYA_CORE_INFO(Move(e));
      EventDispatcher ed(Move(e));

      ed.Dispatch<WindowCloseEvent>([&](Scope<WindowCloseEvent> e) -> bool {
        m_Running = false;
        return true;
        });
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); 
    indexBuffer->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_Window->OnUpdate(); // Swap Buffers

  // TODO: Consider creating a RunLoop class which will update the app for us. We could
  // implement logic by having a new type of event immediately dispatched. This is not
  // needed anytime soon but may be useful when this class becomes to cluttered.
  }
}

} // namespace Papaya
