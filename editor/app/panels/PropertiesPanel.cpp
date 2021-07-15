#include "PropertiesPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>

namespace Papaya
{
  PropertiesPanel::PropertiesPanel()
  {
  }

  PropertiesPanel::PropertiesPanel(Ref<Scene>& scene)
  {
    m_Scene = scene;
  }

  PropertiesPanel::~PropertiesPanel()
  {
  }

  void PropertiesPanel::OnImGuiRender()
  {
    if (m_Open)
    {
      ImGui::Begin("Properties");

      if (m_SelectedEntity) {

        // TAG
        if (m_SelectedEntity.HasComponent<TagComponent>())
          ShowTagMenu(m_SelectedEntity);

        // TRANSFORM
        if (m_SelectedEntity.HasComponent<TransformComponent>())
          ShowTransformMenu(m_SelectedEntity);

        // SPRITE RENDERER
        if (m_SelectedEntity.HasComponent<SpriteRendererComponent>())
          ShowSpriteMenu(m_SelectedEntity);

        // CAMERA
        if (m_SelectedEntity.HasComponent<CameraComponent>())
          ShowCameraMenu(m_SelectedEntity);

      }

      ImGui::End();
    }
  }

  void PropertiesPanel::ShowTagMenu(Entity e)
  {
    int flags = ImGuiTreeNodeFlags_Framed
      | ImGuiTreeNodeFlags_OpenOnArrow
      | ImGuiTreeNodeFlags_OpenOnDoubleClick
      | ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx("Tag", flags))
    {
      auto& tag = e.GetComponent<TagComponent>();

      char buffer[256];
      memset(buffer, 0, sizeof(buffer));
      std::strncpy(buffer, tag.Name.Raw(), sizeof(buffer));
      if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
      {
        tag = String(buffer);
      }

      ImGui::TreePop();
    }
  }

  void PropertiesPanel::ShowTransformMenu(Entity e)
  {
    int flags = ImGuiTreeNodeFlags_Framed
      | ImGuiTreeNodeFlags_OpenOnArrow
      | ImGuiTreeNodeFlags_OpenOnDoubleClick
      | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::TreeNodeEx("Transform", flags))
    {
      auto& transform = e.GetComponent<TransformComponent>();

      ImGui::DragFloat3("Translation", glm::value_ptr(transform.Translation), 0.05f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Rotation", glm::value_ptr(transform.Rotation), 0.05f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.05f, 0.0f, 0.0f, "%.2f");

      ImGui::TreePop();
    }
  }

  void PropertiesPanel::ShowSpriteMenu(Entity e)
  {
    int flags = ImGuiTreeNodeFlags_Framed
      | ImGuiTreeNodeFlags_OpenOnArrow
      | ImGuiTreeNodeFlags_OpenOnDoubleClick
      | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::TreeNodeEx("Sprite Renderer", flags))
    {
      auto& sprite = e.GetComponent<SpriteRendererComponent>();

      ImGui::ColorEdit4("Color", glm::value_ptr(sprite.Color));

      ImGui::TreePop();
    }
  }

  void PropertiesPanel::ShowCameraMenu(Entity e)
  {
    int flags = ImGuiTreeNodeFlags_Framed
      | ImGuiTreeNodeFlags_OpenOnArrow
      | ImGuiTreeNodeFlags_OpenOnDoubleClick
      | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::TreeNodeEx("Camera", flags))
    {
      auto& camera = e.GetComponent<CameraComponent>();

      float zoom = camera.Zoom;
      ImGui::DragFloat("Zoom", &camera.Zoom);
      if (zoom != camera.Zoom)
        camera.RefreshProjection();

      //ImGui::
      if (ImGui::Button("Make Active"))
      {
        m_Scene->SetSceneCamera(e);
      }

      ImGui::TreePop();
    }
  }

} // namespace Papaya