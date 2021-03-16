#include <Papaya/Papaya.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public Papaya::Layer
{
public:
  SandboxLayer()
    : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), Layer("SandboxLayer")
  {
    m_Texture = Papaya::Texture2D::Create("tests/assets/textures/logo.png");
    m_Checkerboard = Papaya::Texture2D::Create("tests/assets/textures/checkboard.png");

    Papaya::FramebufferDesc desc;
    desc.Width = 1280;
    desc.Height = 720;
    m_Framebuffer = Papaya::Framebuffer::Create(desc);
  }

  ~SandboxLayer()
  {
  }

  virtual void OnAttach() override
  {
  }

  virtual void OnDetach() override
  {
  }

  virtual void OnUpdate(Papaya::Timestep ts) override
  {
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

    m_Framebuffer->Bind();
    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer2D::BeginScene(m_Camera);
    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)), m_Texture);
    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -0.4f, 0.0f)), glm::vec4(1.0f));
    Papaya::Renderer2D::EndScene();
    m_Framebuffer->Unbind();

    Papaya::ImGuiRenderer::Begin();

    ImGui::Begin("Scene");
    ImVec2 viewSize = ImGui::GetContentRegionAvail();
    ImGui::Image(*((void**)(&m_Framebuffer->GetColorTexture())), viewSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();

    ImGui::ShowDemoWindow();

    Papaya::ImGuiRenderer::End();

    if (viewSize.x != m_ViewportSize.x || viewSize.y != m_ViewportSize.y)
    {
      m_ViewportSize = glm::vec2(viewSize.x, viewSize.y);
      m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
      
      float width = (1.6f / 1200.0f) * m_ViewportSize.x;
      float height = (1.6f / 1200.0f) * m_ViewportSize.y;
      m_Camera.SetProjection(-width, width, -height, height);
    }
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event>& event) override
  {
    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent* event) {
      float width = (1.6f / 1200.0f) * m_ViewportSize.x;
      float height = (1.6f / 1200.0f) * m_ViewportSize.y;
      m_Camera.SetProjection(-width, width, -height, height);
    });
  }

private:
  Papaya::OrthographicCamera m_Camera;
  Papaya::Ref<Papaya::Texture2D> m_Texture;
  Papaya::Ref<Papaya::Texture2D> m_Checkerboard;
  Papaya::Ref<Papaya::Framebuffer> m_Framebuffer;

  glm::vec2 m_ViewportSize = glm::vec2(0.0f);

  bool m_ShowDemoWindow = true;
};

Papaya::Game* Papaya::CreateGame()
{
  Papaya::Game* game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
