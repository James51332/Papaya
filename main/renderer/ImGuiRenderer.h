#pragma once

#include "main/events/Event.h"

namespace Papaya
{

  class ImGuiRenderer
  {
  public:
    static void OnInit();
    static void OnTerminate();

    static void Begin();
    static void End();

    static void OnEvent(const Scope<Event>& event);
  };

} // namespace Papaya
