#pragma once

#include "main/core/Timestep.h"
#include "main/events/Event.h"

namespace Papaya
{

  class ImGuiRenderer
  {
  public:
    static void OnInit();
    static void OnTerminate();

    static void Begin(Timestep ts);
    static void End();

    static void BlockEvents(bool block);
    static void OnEvent(const Scope<Event>& event);
  };

} // namespace Papaya
