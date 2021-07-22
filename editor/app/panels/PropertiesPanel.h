#pragma once

#include "Panel.h"
#include "main/scene/Entity.h"
#include "main/scene/Components.h"
#include "main/scene/Scene.h"

#include <glm/glm.hpp>

namespace Papaya {

  class PropertiesPanel : public Panel {
  public:
    PropertiesPanel();
    PropertiesPanel(Ref<Scene>& scene);
    ~PropertiesPanel();

    void SetSelectedEntity(Entity e) { m_SelectedEntity = e; }
    void OnImGuiRender();

  private:
    void ShowTagMenu(Entity e);
    void ShowTransformMenu(Entity e);
    void ShowSpriteMenu(Entity e);
    void ShowCameraMenu(Entity e);

  private:
    Ref<Scene> m_Scene;
    Entity m_SelectedEntity;
  };

} // namespace Papaya