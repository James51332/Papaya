#include <Papaya/Papaya.h>

#include "platform/opengl/OpenGLPipelineState.h"
#include "platform/opengl/OpenGLShader.h"

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
    layout (location = 1) in vec2 aTexCoord;

    uniform mat4 u_Camera;

    out vec2 texCoord;

    void main()
    {
      texCoord = aTexCoord;
      gl_Position = u_Camera * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    })";

    Papaya::String fragmentShaderSource = R"(
    #version 330 core

    layout (location = 0) out vec4 color;
    
    in vec2 texCoord;

    uniform sampler2D u_Texture;

    void main()
    {
      color = texture(u_Texture, texCoord);
    })";

    Papaya::Ref<Papaya::Shader> shader = Papaya::Shader::Create(vertexShaderSource, fragmentShaderSource);

    shader->Bind();
    shader->SetInt("u_Texture", 0);

    Papaya::VertexDescriptor layout = {
      {{ Papaya::ShaderDataType::Float3, "aPos" }, { Papaya::ShaderDataType::Float2, "aTexCoord" }}
    };

    Papaya::PipelineStateDesc desc;
    desc.Shader = shader;
    desc.Layout = layout;
    m_PipelineState = Papaya::PipelineState::Create(desc);

    m_Texture = Papaya::Texture2D::Create("tests/assets/textures/checkboard.png");

    float vertices[] = {
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
    };

    uint32_t indices[] = {
        0, 1, 2, // left
        2, 3, 0  // right
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
    
    m_Texture->Bind();
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

  Papaya::Ref<Papaya::Texture2D> m_Texture;

  Papaya::OrthographicCamera m_Camera;
};

Papaya::Game *Papaya::CreateGame()
{
  Papaya::Game *game = new Papaya::Game();
  game->PushLayer(new SandboxLayer());
  return game;
}
