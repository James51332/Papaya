#include "Game.h"


#define PAPAYA_MAIN
#include "EntryPoint.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"
#include "main/events/EventQueue.h"

#include "main/core/Log.h"
#include "main/core/String.h"
#include "main/core/Platform.h"

namespace Papaya
{

Game::Game() {
  m_Window = Window::Create();
}

Game::~Game() {

}

void Game::Run() {
  m_Window->Show();

  while (m_Running) {
    Platform::OnUpdate(); // Poll Events

    while (!EventQueue::Empty()) {
      EventDispatcher e(EventQueue::PopEvent());
      e.Dispatch<WindowCloseEvent>([&](Scope<WindowCloseEvent> e) -> bool {
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
