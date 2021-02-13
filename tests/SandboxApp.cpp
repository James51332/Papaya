#include <Papaya/Papaya.h>

class SandboxLayer : public Papaya::Layer
{
public:
  SandboxLayer()
      : Layer("SandboxLayer")
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

    out vec4 color;

    void main()
    {
      color = vec4(aColor, 1.0);
      gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

    Papaya::BufferLayout layout = {
        {Papaya::ShaderDataType::Float3, "Vertex"}, // Vertices
        {Papaya::ShaderDataType::Float3, "Color"}   // Colors
    };

    Papaya::PipelineStateDesc desc;
    desc.Shader = shader;
    desc.Layout = layout;
    m_PipelineState = Papaya::PipelineState::Create(desc);

    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top

        // second triangle
        0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // right
        0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f  // top
    };

    uint32_t indices[] = {
        0, 1, 2, // left
        3, 4, 5  // right
    };

    m_VertexBuffer = Papaya::Buffer::Create(vertices, sizeof(vertices), Papaya::BufferType::Vertex);
    m_IndexBuffer = Papaya::Buffer::Create(indices, sizeof(indices), Papaya::BufferType::Index);
  }

  virtual void OnDetach() override
  {
  }

  virtual void OnUpdate() override
  {
    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer::Begin();
    Papaya::Renderer::Submit({m_VertexBuffer}, m_PipelineState, m_IndexBuffer);
    Papaya::Renderer::End();
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event> &event) override
  {
  }

private:
  Papaya::Ref<Papaya::Buffer> m_VertexBuffer;
  Papaya::Ref<Papaya::PipelineState> m_PipelineState;
  Papaya::Ref<Papaya::Buffer> m_IndexBuffer;
};

Papaya::Game *Papaya::CreateGame()
{
  Papaya::Game *game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
