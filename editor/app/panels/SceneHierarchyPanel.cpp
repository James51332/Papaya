#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

namespace Papaya {
  
  SceneHierarchyPanel::SceneHierarchyPanel()
  {
    
  }
  
  SceneHierarchyPanel::~SceneHierarchyPanel()
  {
    
  }
  
  void SceneHierarchyPanel::OnImGuiRender()
  {
    ImGui::Begin("Scene Hierarchy", &m_Open);

    ImGui::End();
  }
  
} // namespace Papaya
