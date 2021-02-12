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

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Renderer.h"
#include "main/renderer/RenderCommand.h"

#include "main/utils/String.h"

namespace Papaya
{

Game::Game() {
  WindowAttribs attribs = WindowAttribs();
  attribs.Resizable = true;
  m_Window = Window::Create(attribs);

  Renderer::OnInit();
}

Game::~Game() {

}

void Game::Run() {
    m_Window->Show();

    Ref<Buffer> vertexBuffer;
    Ref<Buffer> indexBuffer;
    Ref<Shader> shader;

    String vertexShaderSource = R"(
    #version 330 core
    
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec4 color;

    void main()
    {
      color = vec4(aColor, 1.0);
      gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    })";

    String fragmentShaderSource = R"(
    #version 330 core

    in vec4 color;
    out vec4 FragColor;

    void main()
    {
      FragColor = color;
    })"; 

    shader = Shader::Create(vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top 
        // second triangle
         0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
         0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // right
         0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f // top 
    };

    uint32_t indices[] = {
      0, 1, 2,
      3, 4, 5
    };

    indexBuffer = Buffer::Create(indices, sizeof(indices), BufferType::Index);
    vertexBuffer = Buffer::Create(vertices, sizeof(vertices), BufferType::Vertex);

    BufferLayout layout = {
      {ShaderDataType::Float3, "Vertex"}, {ShaderDataType::Float3, "Color"}
    };

    while (m_Running)
    {
      Platform::OnUpdate(); // Poll Events

      while (!EventQueue::Empty()) // Process Events
      {
        Scope<Event> e(EventQueue::PopEvent());
        PAPAYA_CORE_INFO(e);
        EventDispatcher ed(Move(e));

        ed.Dispatch<WindowCloseEvent>([&](Scope<WindowCloseEvent> e) -> bool {
          m_Running = false;
          return true;
        });
      }

      RenderCommand::ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      RenderCommand::Clear();

      Renderer::Begin();
      Renderer::Submit({vertexBuffer}, layout, indexBuffer, shader); // Render
      Renderer::End();

      m_Window->OnUpdate(); // Swap Buffers

      // TODO: Consider creating a RunLoop class which will update the app for us. We could
      // implement logic by having a new type of event immediately dispatched. This is not
      // needed anytime soon but may be useful when this class becomes to cluttered.
  }

  Renderer::OnTerminate();
}

} // namespace Papaya
