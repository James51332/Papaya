#pragma once

#include <Papaya/Papaya.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

#include <entt/entt.hpp>

#include "panels/SceneHierarchyPanel.h"
#include "panels/PropertiesPanel.h"
#include "panels/FilesPanel.h"

namespace Papaya
{

  class EditorLayer : public Layer
  {
  public:
    EditorLayer();
    virtual ~EditorLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(const Scope<Event>& event) override;
    virtual void OnImGuiRender() override;
    virtual void OnUpdate(Timestep ts) override;
  private:
    Camera m_EditorCamera;
    Ref<Framebuffer> m_Framebuffer;
    glm::vec2 m_ViewportSize, m_LastViewportSize;
    bool m_Runtime = false;

    Ref<Scene> m_Scene;
    SceneHierarchyPanel m_SceneHierarchyPanel;
    PropertiesPanel m_PropertiesPanel;
    FilesPanel m_FilesPanel;

  };

} // namespace Papaya
