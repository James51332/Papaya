#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  EditorLayer::EditorLayer()
    : Layer("EditorLayer")
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
  }

  void EditorLayer::OnImGuiRender()
  {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Save Scene"))
      {

      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    m_SceneHierarchyPanel.OnImGuiRender();

    m_PropertiesPanel.SetSelectedEntity(m_SceneHierarchyPanel.GetSelectedEntity());
    m_PropertiesPanel.OnImGuiRender();

    m_FilesPanel.OnImGuiRender();

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
    ImGui::Begin("Viewport");

    if (ImGui::Button("Play/Stop"))
      m_Runtime = !m_Runtime;

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
      uint32_t width = static_cast<uint32_t>(m_ViewportSize.x);
      uint32_t height = static_cast<uint32_t>(m_ViewportSize.y);

      m_Framebuffer->Resize(width, height);
      m_EditorCamera.SetViewportSize(width, height);
      m_Scene->SetViewportSize(width, height);
    }

    // We just set up the code to run from here 
    // but this can be run from anywhere! This
    // means we can add it to ImGui panels with
    // only a few lines of code!
    if (!m_Runtime)
    {
      if (Input::KeyPressed(KeyF))
        SceneSerializer::SerializeScene(m_Scene);
      if (Input::KeyPressed(KeyL))
        SceneSerializer::DeserializeScene(m_Scene, "Untitled.pscene");
    }

    m_EditorCamera.OnUpdate(ts, m_Runtime);
    m_EditorCamera.SetPosition({ 0.0f, 0.0f, 10.0f });

    Papaya::RenderCommand::ClearColor(0.1f, 0.1f, 0.1f, 1.1f);
    Papaya::RenderCommand::Clear();

    // The layer probably shouldn't own the 
    // framebuffer. We need to figure out a 
    // more ideal way to handle framebuffers
    // Potentially via having a renderpass hold a target
    // framebuffer.
    m_Framebuffer->Bind();
    RenderCommand::ClearColor(0.0f, 0.0f, 0.0f);
    RenderCommand::Clear();

    if (m_Runtime)
      m_Scene->OnUpdateRuntime(ts);
    else
      m_Scene->OnUpdate(ts, m_EditorCamera);

    m_Framebuffer->Unbind();
  }

} // namespace Papaya
