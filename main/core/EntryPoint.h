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

#include <iostream>

int main() {
  // Lifecycle of game on macOS

  std::cout << "Engine Initializing..." << std::endl;

  auto game = Papaya::CreateGame();
  game->Run();
  delete game;
}
#endif // PAPAYA_MAIN
#endif // PAPAYA_MACOS

#endif /* end of include guard: EntryPoint_h */