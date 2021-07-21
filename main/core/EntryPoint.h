#pragma once

// Entrypoint to engine. This file is include with PAPAYA_MAIN defined in Game.cpp

#ifdef PAPAYA_MACOS

#include "Game.h"
#include "Platform.h"
#include "Log.h"

namespace Papaya
{
extern Game* CreateGame();
} // namespace Papaya

#ifdef PAPAYA_MAIN

int main() {
  // Lifecycle of game on macOS
  Papaya::Log::OnInit();
  PAPAYA_CORE_TRACE("Engine Initializing...");

  Papaya::Platform::OnInit();

  auto game = Papaya::CreateGame();
  game->Run();
  delete game;

  Papaya::Platform::OnTerminate();
}
#endif // PAPAYA_MAIN
#endif // PAPAYA_MACOS

#ifdef PAPAYA_WINDOWS

#include "Game.h"
#include "Platform.h"
#include "Log.h"

namespace Papaya
{
extern Game* CreateGame();
} // namespace Papaya

#ifdef PAPAYA_MAIN

int main() {
  // Lifecycle of game on windows
  Papaya::Log::OnInit();
  PAPAYA_CORE_TRACE("Engine Initializing...");

  Papaya::Platform::OnInit();

  auto game = Papaya::CreateGame();
  game->Run();
  delete game;

  Papaya::Platform::OnTerminate();
}
#endif // PAPAYA_MAIN
#endif // PAPAYA_WINDOWS
