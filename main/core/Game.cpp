#include "Game.h"

#include "Log.h"

#define PAPAYA_MAIN
#include "EntryPoint.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"
#include "main/events/EventQueue.h"

#include "main/core/String.h"

#include "main/core/Platform.h"

namespace Papaya
{

Game::Game() {

}

Game::~Game() {

}

void Game::Run() {
  // THE ENTRY TO ENGINE
  EventQueue::PushEvent(CreateScope<WindowResizeEvent>(800, 600));
  EventQueue::PushEvent(CreateScope<WindowCloseEvent>());
  EventQueue::PushEvent(CreateScope<MousePressEvent>(0));

  PAPAYA_CORE_INFO(EventQueue::PopEvent()); // These should pop off in same order
  PAPAYA_CORE_INFO(EventQueue::PopEvent()); // Resize, Close, Mouse
  PAPAYA_CORE_INFO(EventQueue::PopEvent());

  String s = "This is printed from a Papaya String!";
  PAPAYA_CORE_INFO(s);

  while (true);
  //Platform::OnUpdate();
}

} // namespace Papaya
