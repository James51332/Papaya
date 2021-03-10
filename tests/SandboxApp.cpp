#include <Papaya/Papaya.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

class SandboxLayer : public Papaya::Layer
{
public:
  SandboxLayer()
      : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), Layer("SandboxLayer")
  {
    m_Texture = Papaya::Texture2D::Create("tests/assets/textures/logo.png");
  }

  ~SandboxLayer()
  {
  }

  virtual void OnAttach() override
  {
      ImGui::CreateContext();
      ImGui::StyleColorsDark();
      
      ImGuiIO& io = ImGui::GetIO();
      io.DisplaySize.x = 1280;
      io.DisplaySize.y = 720;
      
      Papaya::ImGui_Init();
  }

  virtual void OnDetach() override
  {
  }

  virtual void OnUpdate(Papaya::Timestep ts) override
  {
    //PAPAYA_TRACE("FPS: {}", 1 / ts);

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

    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer2D::BeginScene(m_Camera);

    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -0.4f, 0.0f)), glm::vec4(1.0f));
    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)), m_Texture);

    Papaya::Renderer2D::EndScene();
      
    ImGui::NewFrame();

    if (m_ShowDemoWindow)
        ImGui::ShowDemoWindow();

      ImGui::Render();
      Papaya::ImGui_Render();
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event> &event) override
  {
    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent *event) {
      float width = (1.6f / 1200.0f) * event->GetWidth();
      float height = (1.6f / 1200.0f) * event->GetHeight();
        
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = event->GetWidth();
        io.DisplaySize.y = event->GetHeight();

      m_Camera.SetProjection(-width, width, -height, height);
    });
  }

private:
  Papaya::OrthographicCamera m_Camera;
  Papaya::Ref<Papaya::Texture2D> m_Texture;
  Papaya::Ref<Papaya::Texture2D> m_Checkerboard;
  Papaya::Ref<Papaya::Buffer> m_VertexBuffer;
  Papaya::Ref<Papaya::Buffer> m_IndexBuffer;
  Papaya::Ref<Papaya::PipelineState> m_PipelineState;
    bool m_ShowDemoWindow = true;
};

Papaya::Game *Papaya::CreateGame()
{
  Papaya::Game *game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
