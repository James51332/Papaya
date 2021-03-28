#pragma once

#include <Papaya/Papaya.h>

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
    virtual void OnUpdate(Timestep ts) override;
  private:
    Papaya::OrthographicCamera m_Camera;
    Papaya::Ref<Papaya::Texture2D> m_Texture;
    Papaya::Ref<Papaya::Texture2D> m_Checkerboard;
    Papaya::Ref<Papaya::Framebuffer> m_Framebuffer;

    glm::vec2 m_ViewportSize = glm::vec2(0.0f);
  };

} // namespace Papaya
