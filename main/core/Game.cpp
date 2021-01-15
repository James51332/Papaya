#include "Game.h"

#include "Log.h"

#define PAPAYA_MAIN
#include "EntryPoint.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"

namespace Papaya
{

Game::Game() {

}

Game::~Game() {

}

void Game::Run() {
  // THE ENTRY TO ENGINE

  WindowResizeEvent e(800, 600);
  PAPAYA_CORE_INFO(e);

  while (true);
}

} // namespace Papaya
