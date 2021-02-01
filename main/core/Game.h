#ifndef Game_h
#define Game_h

#include "main/core/Window.h"

namespace Papaya
{

class Game {
public:
  Game();
  virtual ~Game();

  void Run();
private:
  Scope<Window> m_Window;
  Ref<Context> m_Context;

  bool m_Running = true;
};

} // namespace Papaya

#endif /* end of include guard: Game_h */