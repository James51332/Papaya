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

//#include "platform/OpenGL/OpenGLLoader.h"

#include <GL/GL.h>

namespace Papaya
{

Game::Game() {
  m_Window = Window::Create();
}

Game::~Game() {

}

void Game::Run() {
  m_Window->Show();

  // const char* vertexShaderSource = "#version 330 core\n"
  //   "layout (location = 0) in vec3 aPos;\n"
  //   "void main()\n"
  //   "{\n"
  //   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  //   "}\0";
  // const char* fragmentShaderSource = "#version 330 core\n"
  //   "out vec4 FragColor;\n"
  //   "void main()\n"
  //   "{\n"
  //   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  //   "}\n\0";

  // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // glCompileShader(vertexShader);
  // // check for shader compile errors
  // // int success;
  // // char infoLog[512];
  // // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  // // if (!success)
  // // {
  // //   glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  // //   PAPAYA_ASSERT(false, "Failed to compile vertex Shader!");
  // // }
  // // // fragment shader
  // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  // glCompileShader(fragmentShader);
  // // // check for shader compile errors
  // // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  // // if (!success)
  // // {
  // //   glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  // //   PAPAYA_ASSERT(false, "Failed to compile fragment Shader!");
  // // }
  // // // link shaders
  // unsigned int shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);
  // glLinkProgram(shaderProgram);

  // //glDeleteShader(vertexShader);
  // //glDeleteShader(fragmentShader);

  // // set up vertex data (and buffer(s)) and configure vertex attributes
  // // ------------------------------------------------------------------
  // // add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
  // float vertices[] = {
  //   // first triangle
  //  -0.9f, -0.5f, 0.0f,  // left 
  //   -0.0f, -0.5f, 0.0f,  // right
  //   -0.45f, 0.5f, 0.0f,  // top 
  //   // second triangle
  //    0.0f, -0.5f, 0.0f,  // left
  //    0.9f, -0.5f, 0.0f,  // right
  //    0.45f, 0.5f, 0.0f   // top 
  // };

  // GLuint VBO, VAO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  // glBindVertexArray(VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);

  // // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  // glBindVertexArray(0);
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

    // glClear(GL_TRIANGLES);
    // glVertex2f(0.0f, 0.5f);
    // glVertex2f(0.5f, 0.5f);
    // glVertex2f(-0.5f, -0.5f);
    // glEnd();

      // glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      // glClear(GL_COLOR_BUFFER_BIT);

      // // // draw our first triangle
      // glUseProgram(shaderProgram);
      // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      // glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
      // // // glBindVertexArray(0); // no need to unbind it every time

      m_Window->OnUpdate(); // Swap Buffers

    // TODO: Consider creating a RunLoop class which will update the app for us. We could
    // implement logic by having a new type of event immediately dispatched. This is not
    // needed anytime soon but may be useful when this class becomes to cluttered.
  }
}

} // namespace Papaya
