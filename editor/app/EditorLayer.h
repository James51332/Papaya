#pragma once

#include <Papaya/Papaya.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

#include <entt/entt.hpp>

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
    OrthographicCamera m_Camera;
    Ref<Texture2D> m_Texture;
    Ref<Texture2D> m_Checkerboard;
    Ref<Framebuffer> m_Framebuffer;
    Ref<Scene> m_Scene;

    glm::vec2 m_ViewportSize, m_LastViewportSize;
  };

} // namespace Papaya
