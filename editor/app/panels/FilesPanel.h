#pragma once

#include "Panel.h"
#include "main/scene/Scene.h"

namespace Papaya {

  class FilesPanel : public Panel {
  public:
    FilesPanel();
    FilesPanel(Ref<Scene>& scene);
    ~FilesPanel();

    void OnImGuiRender();

  private:
    Ref<Scene> m_Scene;
    String m_CurrentDirectory;
  };

} // namespace Papaya