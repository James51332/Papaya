#include "EditorLayer.h"

namespace Papaya
{

  EditorLayer::EditorLayer()
    : m_Camera(-16.0f, 16.0f, -9.0f, 9.0f), Layer("EditorLayer")
  {
    Papaya::FramebufferDesc desc;
    desc.Width = 1280;
    desc.Height = 720;
    m_Framebuffer = Papaya::Framebuffer::Create(desc);
  
    m_Scene = CreateRef<Scene>();
    m_SceneHierarchyPanel = SceneHierarchyPanel(m_Scene);
    m_PropertiesPanel = PropertiesPanel(m_Scene);

    Entity e = m_Scene->CreateEntity("Sprite");
    e.AddComponent<TransformComponent>();
    e.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f));
  }

  EditorLayer::~EditorLayer()
  {

  }

  void EditorLayer::OnAttach()
  {

  }

  void EditorLayer::OnDetach()
  {
  }

  void EditorLayer::OnEvent(const Scope<Event>& event)
  {
    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent* event) {
      float width = (1.6f / 1200.0f) * m_ViewportSize.x;
      float height = (1.6f / 1200.0f) * m_ViewportSize.y;
      m_Camera.SetProjection(-width, width, -height, height);
      });
  }
  
  void EditorLayer::OnImGuiRender()
  {
    
    m_SceneHierarchyPanel.OnImGuiRender();

    m_PropertiesPanel.SetSelectedEntity(m_SceneHierarchyPanel.GetSelectedEntity());
    m_PropertiesPanel.OnImGuiRender();

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
    ImGui::Begin("Viewport");
    
    // ImGui should block events unless the viewport is in focus
    ImGuiRenderer::BlockEvents(!ImGui::IsWindowFocused() && !ImGui::IsWindowHovered());

    ImVec2 viewSize = ImGui::GetContentRegionAvail();
    ImGui::Image(reinterpret_cast<void*>(&m_Framebuffer->GetColorTexture()), viewSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    
    m_LastViewportSize = m_ViewportSize;
    m_ViewportSize = glm::vec2(viewSize.x, viewSize.y);
    
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void EditorLayer::OnUpdate(Timestep ts)
  {
    if (m_ViewportSize != m_LastViewportSize)
    {
      m_Framebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));

      float width = (1.6f / 1200.0f) * m_ViewportSize.x;
      float height = (1.6f / 1200.0f) * m_ViewportSize.y;
      m_Camera.SetProjection(-width, width, -height, height);
    }

    if (Papaya::Input::KeyDown(Papaya::KeyW))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, 4.0f * ts, 0.0f));
    if (Papaya::Input::KeyDown(Papaya::KeyS))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, -4.0f * ts, 0.0f));
    if (Papaya::Input::KeyDown(Papaya::KeyD))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(4.0f * ts, 0.0f, 0.0f));
    if (Papaya::Input::KeyDown(Papaya::KeyA))
      m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-4.0f * ts, 0.0f, 0.0f));

    if (Papaya::Input::KeyDown(Papaya::KeyLeft))
      m_Camera.SetRotation(static_cast<float>(m_Camera.GetRotation() - 200.0f * ts));
    if (Papaya::Input::KeyDown(Papaya::KeyRight))
      m_Camera.SetRotation(static_cast<float>(m_Camera.GetRotation() + 200.0f * ts));

    Papaya::RenderCommand::ClearColor(0.1f, 0.1f, 0.1f, 1.1f);
    Papaya::RenderCommand::Clear();

    // The layer probably shouldn't own the 
    // framebuffer. We need to figure out a 
    // more ideal way to handle cameras and framebuffers
    m_Framebuffer->Bind(); 

    RenderCommand::ClearColor(0.0f, 0.0f, 0.0f);
    RenderCommand::Clear();

    m_Scene->OnUpdate(ts, m_Camera);
    
    m_Framebuffer->Unbind();
  }

} // namespace Papaya
