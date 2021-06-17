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

        ImGui::PushID(static_cast<uint32_t>(entity));
        if (ImGui::Selectable(e.GetComponent<TagComponent>().Name.Raw(), e == m_SelectedEntity))
          m_SelectedEntity = e;
        ImGui::PopID();

        ShowItemMenu(e);
      });

      ImGui::End();
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
    if (ImGui::BeginPopupContextItem())
    {
      if (ImGui::BeginMenu("Add Component"))
      {
        if (ImGui::MenuItem("Transform Component"))
          e.AddComponent<TransformComponent>();

        if (ImGui::MenuItem("SpriteRenderer Component"))
        {
          if (!e.HasComponent<TransformComponent>())
            e.AddComponent<TransformComponent>();

          e.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f));
        }
      
        ImGui::EndMenu();
      }

      if (ImGui::MenuItem("Delete Entity")) {
        if (m_SelectedEntity == e)
          m_SelectedEntity = { m_Scene.get(), entt::null };

        e.Destroy();
      }

      ImGui::EndPopup();
    }
  }

} // namespace Papaya
