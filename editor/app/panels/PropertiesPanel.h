#pragma once

#include "Panel.h"

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include "main/scene/Scene.h"
#include "main/scene/Components.h"
#include "main/scene/Entity.h"

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
    void ShowTransformMenu(Entity e);
    void ShowSpriteMenu(Entity e);

  private:
    Ref<Scene> m_Scene;
    Entity m_SelectedEntity;
  };

} // namespace Papaya