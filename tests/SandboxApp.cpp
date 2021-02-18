#include <Papaya/Papaya.h>

class SandboxLayer : public Papaya::Layer
{
public:
  SandboxLayer()
      : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), Layer("SandboxLayer")
  {
  }

  ~SandboxLayer()
  {
  }

  virtual void OnAttach() override
  {
    Papaya::String vertexShaderSource = R"(
    #version 330 core
    
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    uniform mat4 u_Camera;

    out vec4 color;

    void main()
    {
      color = vec4(aColor, 1.0);
      gl_Position = u_Camera * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    })";

    Papaya::String fragmentShaderSource = R"(
    #version 330 core

    in vec4 color;
    out vec4 FragColor;

    void main()
    {
      FragColor = color;
    })";

    Papaya::Ref<Papaya::Shader> shader = Papaya::Shader::Create(vertexShaderSource, fragmentShaderSource);

    Papaya::VertexDescriptor layout = {
        {{Papaya::ShaderDataType::Float3, "Vertex"}, {Papaya::ShaderDataType::Float3, "Color"}} // Colors
    };

    Papaya::PipelineStateDesc desc;
    desc.Shader = shader;
    desc.Layout = layout;
    m_PipelineState = Papaya::PipelineState::Create(desc);

    float vertices[] = {
        // first triangle
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f, // left
        -0.0f,
        -0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f, // left
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f, // left

        // second triangle
        0.0f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.9f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.45f,
        0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
    };

    uint32_t indices[] = {
        0, 1, 2, // left
        3, 4, 5  // right
    };

    m_VertexBuffer = Papaya::Buffer::Create(vertices, sizeof(vertices), Papaya::BufferType::Vertex, Papaya::BufferUsage::Immutable);
    m_IndexBuffer = Papaya::Buffer::Create(indices, sizeof(indices), Papaya::BufferType::Index, Papaya::BufferUsage::Immutable);
  }

  virtual void OnDetach() override
  {
  }

  virtual void OnUpdate(Papaya::Timestep t) override
  {
    double fps = 1 / t;
    PAPAYA_INFO("FPS: {}", fps);

    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer::Begin(m_Camera);
    Papaya::Renderer::Submit(m_VertexBuffer, m_PipelineState, m_IndexBuffer);
    Papaya::Renderer::End();
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event> &event) override
  {
    PAPAYA_INFO(event);

    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent *event) {
      float width = (1.6f / 1200.0f) * event->GetWidth();
      float height = (1.6f / 1200.0f) * event->GetHeight();

      m_Camera.SetProjection(-width, width, -height, height);
    });
  }

private:
  Papaya::Ref<Papaya::Buffer> m_VertexBuffer;
  Papaya::Ref<Papaya::Buffer> m_IndexBuffer;
  Papaya::Ref<Papaya::PipelineState> m_PipelineState;

  Papaya::OrthographicCamera m_Camera;
};

Papaya::Game *Papaya::CreateGame()
{
  Papaya::Game *game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
