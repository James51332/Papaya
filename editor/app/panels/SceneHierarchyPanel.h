#pragma once

#include "Panel.h"

#include "main/utils/Memory.h"

#include "main/scene/Scene.h"

namespace Papaya {

class SceneHierarchyPanel : public Panel
{
public:
  SceneHierarchyPanel();
  ~SceneHierarchyPanel();
  
  void OnImGuiRender();
  
private:
  Ref<Scene> m_Scene;
};
  
} // namespace Papaya
