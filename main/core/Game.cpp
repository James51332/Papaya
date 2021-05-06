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
#include "main/core/Input.h"

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Renderer.h"
#include "main/renderer/RenderCommand.h"
#include "main/renderer/ImGuiRenderer.h"

#include "main/utils/String.h"

#include "Thread.h"

#include <imgui/imgui.h>

namespace Papaya
{

  Game* Game::s_Instance = nullptr;

  Game::Game(const String& title)
  {
    if (s_Instance)
    {
      PAPAYA_ASSERT(false, "Only one instance of Game may be created!");
    }
    s_Instance = this;

    WindowAttribs attribs = WindowAttribs(1200, 675, title, true);
    m_Window = Window::Create(attribs);

    Input::OnInit();
    Renderer::OnInit();
  }

  Game::~Game()
  {
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

  void Game::Run()
  {
    m_Window->Show();

    while (m_Running)
    {
      double time = Platform::GetSysTime();
      Timestep timestep = time - m_TimeSinceLastFrame;

      // if (timestep < 1.0f / 60.0f)
      //   continue;

      m_TimeSinceLastFrame = time;

      Platform::OnUpdate(); // Poll Events

      while (!EventQueue::Empty()) // Process Events
      {
        Scope<Event> e(EventQueue::PopEvent());
        //PAPAYA_CORE_INFO(e);

        EventDispatcher::Dispatch<WindowCloseEvent>(e, [&](WindowCloseEvent* event) {
          m_Running = false;
          // continue; // Don't pass window close events to user (this isn't techinally needed)
          });

        EventDispatcher::Dispatch<WindowResizeEvent>(e, [](WindowResizeEvent* event) {
          RenderCommand::SetViewport(0, 0, event->GetWidth(), event->GetHeight());
          });

        ImGuiRenderer::OnEvent(e); // Call this first because it blocks events in some cases
        Input::OnEvent(e);

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
          (*it)->OnEvent(e);
        }
      }

      Input::OnUpdate(); // Update Input Class

      for (Layer* layer : m_LayerStack) // Update Layers
        layer->OnUpdate(timestep);
      
      ImGuiRenderer::Begin();
      for (Layer* layer : m_LayerStack) // Render ImGui
        layer->OnImGuiRender();
      ImGuiRenderer::End();

      m_Window->OnUpdate(); // Swap Buffers

      // TODO: Consider creating a RunLoop class which will update the app for us. We could
      // implement logic by having a new type of event immediately dispatched. This is not
      // needed anytime soon but may be useful when this class becomes too cluttered.
    }

    Renderer::OnTerminate();
    m_Window->Close(); // Windows don't close until the app is closed or Window::Close() is called
  }

} // namespace Papaya
