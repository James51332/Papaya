#pragma once

#include "main/core/Window.h"
#include "main/core/LayerStack.h"
#include "main/core/Timestep.h"

#include "main/utils/Memory.h"

#include "main/renderer/Camera.h"

namespace Papaya
{

  class Game
  {
  public:
    Game(const String& title = "Papaya");
    virtual ~Game();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

    void Run();
      
    const Scope<Window>& GetWindow() const { return m_Window; }
    static Game* Get() { return s_Instance; }

  private:
    static Game* s_Instance;
  private:
    Scope<Window> m_Window;
    Ref<Context> m_Context;
    LayerStack m_LayerStack;
    Timestep m_TimeSinceLastFrame;

    bool m_Running = true;
  };

} // namespace Papaya
