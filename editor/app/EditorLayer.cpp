#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  EditorLayer::EditorLayer()
    : m_EditorCamera(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f)), Layer("EditorLayer")
  {
    Papaya::FramebufferDesc desc;
    desc.Width = 1280;
    desc.Height = 720;
    m_Framebuffer = Papaya::Framebuffer::Create(desc);
  
    m_Scene = CreateRef<Scene>();
    m_SceneHierarchyPanel = SceneHierarchyPanel(m_Scene);
    m_PropertiesPanel = PropertiesPanel(m_Scene);
    m_FilesPanel = FilesPanel(m_Scene);
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
      m_EditorCamera.SetProjectionMatrix(glm::ortho(-width, width, -height, height));
      });
  }
  
  void EditorLayer::OnImGuiRender()
  {
    
    m_SceneHierarchyPanel.OnImGuiRender();

    m_PropertiesPanel.SetSelectedEntity(m_SceneHierarchyPanel.GetSelectedEntity());
    m_PropertiesPanel.OnImGuiRender();

    m_FilesPanel.OnImGuiRender();

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
    ImGui::Begin("Viewport");
    
    // ImGui should block events unless the viewport is in focus
    ImGuiRenderer::BlockEvents(!ImGui::IsWindowFocused()); // && !ImGui::IsWindowHovered());

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
      m_EditorCamera.SetProjectionMatrix(glm::ortho(-width, width, -height, height));
    }

    if (Input::KeyDown(Papaya::KeyW))
      m_EditorCamera.SetPosition(m_EditorCamera.GetPosition() + glm::vec3(0.0f, 4.0f * ts, 0.0f));
    if (Input::KeyDown(Papaya::KeyS))
      m_EditorCamera.SetPosition(m_EditorCamera.GetPosition() + glm::vec3(0.0f, -4.0f * ts, 0.0f));
    if (Input::KeyDown(Papaya::KeyD))
      m_EditorCamera.SetPosition(m_EditorCamera.GetPosition() + glm::vec3(4.0f * ts, 0.0f, 0.0f));
    if (Input::KeyDown(Papaya::KeyA))
      m_EditorCamera.SetPosition(m_EditorCamera.GetPosition() + glm::vec3(-4.0f * ts, 0.0f, 0.0f));

    if (Input::KeyPressed(KeyF)) {
      // We just set up the code to run from here 
      // but this can be run from anywhere! This
      // means we can add it to ImGui panels with
      // only a few lines of code!
      SceneSerializer::SerializeScene(m_Scene); 
    }

    if (Input::KeyPressed(KeyL)) {
      // We just set up the code to run from here 
      // but this can be run from anywhere! This
      // means we can add it to ImGui panels with
      // only a few lines of code!
      SceneSerializer::DeserializeScene(m_Scene, "Untitled.pscene");
    }
    
    if (Papaya::Input::KeyDown(Papaya::KeyLeft))
      m_EditorCamera.SetRotation(static_cast<float>(m_EditorCamera.GetRotation() - 200.0f * ts));
    if (Papaya::Input::KeyDown(Papaya::KeyRight))
      m_EditorCamera.SetRotation(static_cast<float>(m_EditorCamera.GetRotation() + 200.0f * ts));

    Papaya::RenderCommand::ClearColor(0.1f, 0.1f, 0.1f, 1.1f);
    Papaya::RenderCommand::Clear();

    // The layer probably shouldn't own the 
    // framebuffer. We need to figure out a 
    // more ideal way to handle cameras and framebuffers
    m_Framebuffer->Bind(); 

    RenderCommand::ClearColor(0.0f, 0.0f, 0.0f);
    RenderCommand::Clear();

    if (Input::KeyDown(KeyR))
      m_Scene->OnUpdateRuntime(ts);
    else
      m_Scene->OnUpdate(ts, m_EditorCamera);
    
    m_Framebuffer->Unbind();
  }

} // namespace Papaya
