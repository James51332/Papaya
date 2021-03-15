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
    m_Checkerboard = Papaya::Texture2D::Create("tests/assets/textures/checkboard.png");
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

    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer2D::BeginScene(m_Camera);

    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)), m_Texture);
    Papaya::Renderer2D::DrawQuad(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -0.4f, 0.0f)), glm::vec4(1.0f));

    Papaya::Renderer2D::EndScene();

    Papaya::ImGuiRenderer::Begin();

    ImGui::Begin("FPS");
    ImGui::Text("FPS: %i", static_cast<int>(std::round(1 / ts)));
    ImGui::Image(*((void**)(&m_Checkerboard)), { 100, 100 });
    ImGui::End();

    ImGui::ShowDemoWindow();

    Papaya::ImGuiRenderer::End();
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event>& event) override
  {
    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent* event) {
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

  bool m_ShowDemoWindow = true;
};

Papaya::Game* Papaya::CreateGame()
{
  Papaya::Game* game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
