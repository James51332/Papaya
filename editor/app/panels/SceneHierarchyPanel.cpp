#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

namespace Papaya {

  SceneHierarchyPanel::SceneHierarchyPanel()
  {

  }

  SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene>& scene)
  {
    m_Scene = scene;
  }

  SceneHierarchyPanel::~SceneHierarchyPanel()
  {

  }

  void SceneHierarchyPanel::OnImGuiRender()
  {
    if (m_Open) {
      ImGui::Begin("Scene Hierarchy");

      ShowWindowMenu();

      m_Scene->m_Registry.each([&](entt::entity entity) {
        Entity e = { m_Scene.get(), entity };

        ImGui::PushID(static_cast<int>(e.m_Entity));
        if (ImGui::Selectable(e.GetComponent<TagComponent>().Name.Raw(), e == m_SelectedEntity))
          m_SelectedEntity = e;
        ImGui::PopID();

        ShowItemMenu(e);
        });

      ImGui::End();

      ImGui::Begin("Properties");
      ImGui::End();

      ImGui::ShowDemoWindow();
    }
  }

  void SceneHierarchyPanel::ShowWindowMenu()
  {
    if (ImGui::BeginPopupContextWindow()) {
      if (ImGui::MenuItem("Create Empty Entity"))
        m_Scene->CreateEntity();

      ImGui::EndPopup();
    }
  }

  void SceneHierarchyPanel::ShowItemMenu(Entity e)
  {
    if (ImGui::BeginPopupContextItem()) //(const char*)(void*)e.m_Entity))
    {
      if (ImGui::MenuItem("Delete Entity"))
        e.Destroy();

      if (ImGui::BeginMenu("Add Component"))
      {
        if (ImGui::MenuItem("Transform"))
          e.AddComponent<TransformComponent>(0.0f, 0.0f, 0.0f);
      
        ImGui::EndMenu();
      }

      ImGui::EndPopup();
    }
  }

} // namespace Papaya
