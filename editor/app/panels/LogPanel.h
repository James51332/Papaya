#pragma once

#include "Panel.h"

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include "main/scene/Scene.h"

namespace Papaya {

  class LogPanel : public Panel {
  public:
    LogPanel();
    LogPanel(Ref<Scene>& scene);
    ~LogPanel();

    void OnImGuiRender();

  private:
    Ref<Scene> m_Scene;
  };

} // namespace Papaya