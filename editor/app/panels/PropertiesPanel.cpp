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

      ImGui::TextWrapped("We'll eventually show all the different UI widgets for editing each of the components here. (and we'll make them look prettier ;)");
      
      if (m_SelectedEntity) {

        // TRANSFORM
				if (m_SelectedEntity.HasComponent<TransformComponent>())
				{
          ShowTransformMenu(m_SelectedEntity);
				}

        // SPRITE RENDERER

      }

      ImGui::End();
    
      ImGui::ShowDemoWindow();
    }
  }

  void PropertiesPanel::ShowTransformMenu(Entity e)
  {
    auto& transform = e.GetComponent<TransformComponent>();
    
    ImGui::DragFloat3("Translation", glm::value_ptr(transform.Translation));
    ImGui::DragFloat3("Rotation", glm::value_ptr(transform.Rotation));
    ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale));
  }

  void PropertiesPanel::ShowSpriteMenu(Entity e)
  {
    
  }

} // namespace Papaya