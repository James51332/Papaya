#pragma once

#include "Panel.h"

#include "main/utils/Memory.h"

#include "main/scene/Scene.h"
#include "main/scene/Components.h"
#include "main/scene/Entity.h"

namespace Papaya {

class SceneHierarchyPanel : public Panel
{
public:
  SceneHierarchyPanel();
  SceneHierarchyPanel(Ref<Scene>& scene);
  ~SceneHierarchyPanel();
  
  void OnImGuiRender();

  Entity GetSelectedEntity() { return m_SelectedEntity; }
  void SetSelectedEntity(Entity e) { m_SelectedEntity = e; }
  
private:
  void ShowWindowMenu();
  void ShowItemMenu(Entity e);

private:
  Ref<Scene> m_Scene;
  Entity m_SelectedEntity;
};
  
} // namespace Papaya
