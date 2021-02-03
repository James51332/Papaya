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
  m_Window = Window::Create(WindowAttribs(800, 600, "Papaya", true));

  m_Context = Context::Create(RenderApi::OpenGL);
  m_Window->SetContext(m_Context);
}

Game::~Game() {

}

void Game::Run() {
  m_Window->Show();
  PAPAYA_CORE_TRACE("Created Window: {}", m_Window);

  while (m_Running) {
    Platform::OnUpdate(); // Poll Events

    m_Context->OnUpdate();

    while (!EventQueue::Empty()) { // Process Events
      Scope<Event> e(EventQueue::PopEvent());
      PAPAYA_CORE_INFO(Move(e));
      EventDispatcher ed(Move(e));

      ed.Dispatch<WindowCloseEvent>([&](Scope<WindowCloseEvent> e) -> bool {
        m_Running = false;
        return true;
        });
    }

    // TODO: Consider creating a RunLoop class which will update the app for us. We could
    // implement logic by having a new type of event immediately dispatched. This is not
    // needed anytime soon but may be useful when this class becomes to cluttered.
  }
}

} // namespace Papaya
