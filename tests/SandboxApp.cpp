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

    m_Shader = Papaya::Shader::Create(vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
      // first triangle
      -0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left
      -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
      -0.45f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top
      
      // second triangle
      0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// left
      0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// right
      0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f		// top
    };

    uint32_t indices[] = {
        0, 1, 2,
        3, 4, 5
    };

    m_VertexBuffer = Papaya::Buffer::Create(vertices, sizeof(vertices), Papaya::BufferType::Vertex);
    m_IndexBuffer = Papaya::Buffer::Create(indices, sizeof(indices), Papaya::BufferType::Index);

    m_BufferLayout = {
      {Papaya::ShaderDataType::Float3, "Vertex"}, {Papaya::ShaderDataType::Float3, "Color"}
    };
  }

  virtual void OnDetach() override
  {

  }

  virtual void OnUpdate() override
  {
    Papaya::RenderCommand::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Papaya::RenderCommand::Clear();

    Papaya::Renderer::Begin();
    Papaya::Renderer::Submit({ m_VertexBuffer }, m_BufferLayout, m_IndexBuffer, m_Shader);
    Papaya::Renderer::End();
  }

  virtual void OnEvent(const Papaya::Scope<Papaya::Event>& event) override
  {

  }

private:
  Papaya::Ref<Papaya::Buffer> m_VertexBuffer;
  Papaya::BufferLayout m_BufferLayout;
  Papaya::Ref<Papaya::Shader> m_Shader;
  Papaya::Ref<Papaya::Buffer> m_IndexBuffer;

};

Papaya::Game* Papaya::CreateGame() {
  Papaya::Game* game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
