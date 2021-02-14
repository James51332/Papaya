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

#include "platform/opengl/OpenGLLoader.h"

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

void Game::PushLayer(Layer* layer)
{
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Game::PushOverlay(Layer* overlay)
{
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

void Game::Run() {
    m_Window->Show();

    while (m_Running)
    {
      Platform::OnUpdate(); // Poll Events

      while (!EventQueue::Empty()) // Process Events
      {
        Scope<Event> e(EventQueue::PopEvent());
        PAPAYA_CORE_INFO(e);

        if (e->GetEventType() == EventType::WindowClose)
        {
          m_Running = false;
          continue; // Don't pass window close events to user (this isn't techinally needed)
        }

        if (e->GetEventType() == EventType::WindowResize)
        {
            WindowResizeEvent* event = static_cast<WindowResizeEvent*>(e.get());
            RenderCommand::SetViewport(0, 0, event->GetWidth(), event->GetHeight());
        }

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
          (*it)->OnEvent(e);
        }
      }

      for (Layer* layer : m_LayerStack)
        layer->OnUpdate();

      m_Window->OnUpdate(); // Swap Buffers

      // TODO: Consider creating a RunLoop class which will update the app for us. We could
      // implement logic by having a new type of event immediately dispatched. This is not
      // needed anytime soon but may be useful when this class becomes to cluttered.
  }

  Renderer::OnTerminate();
  m_Window->Close(); // Windows don't close until the app is closed or Close() is called
}

} // namespace Papaya
