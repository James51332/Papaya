#ifndef Game_h
#define Game_h

#include "main/core/Window.h"
#include "main/core/LayerStack.h"

#include "main/utils/Memory.h"

namespace Papaya
{

class Game {
public:
  Game();
  virtual ~Game();

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

  void Run();
private:
  Scope<Window> m_Window;
  Ref<Context> m_Context;
  LayerStack m_LayerStack;

  bool m_Running = true;
};

} // namespace Papaya

#endif /* end of include guard: Game_h */