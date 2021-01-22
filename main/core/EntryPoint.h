#ifndef EntryPoint_h
#define EntryPoint_h

// Entrypoint to engine. This file is include with PAPAYA_MAIN defined in Game.cpp

#ifdef PAPAYA_MACOS

#include "Game.h"

namespace Papaya
{
extern Game* CreateGame();
} // namespace Papaya

#ifdef PAPAYA_MAIN

#include "Log.h"

int main() {
  // Lifecycle of game on macOS
  Papaya::Log::OnInit();
  PAPAYA_CORE_INFO("Engine Initializing...");

  auto game = Papaya::CreateGame();
  game->Run();
  delete game;
}
#endif // PAPAYA_MAIN
#endif // PAPAYA_MACOS

#ifdef PAPAYA_WINDOWS

#include "Game.h"

namespace Papaya
{
extern Game* CreateGame();
} // namespace Papaya

#ifdef PAPAYA_MAIN

#include "Log.h"

int main() {
  // Lifecycle of game on windows
  Papaya::Log::OnInit();
  PAPAYA_CORE_INFO("Engine Initializing...");

  auto game = Papaya::CreateGame();
  game->Run();
  delete game;
}
#endif // PAPAYA_MAIN
#endif // PAPAYA_WINDOWS

#endif /* end of include guard: EntryPoint_h */
