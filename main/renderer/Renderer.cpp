#include "Renderer.h"

#include "RenderCommand.h"
#include "Renderer2D.h"

#include "platform/opengl/OpenGLPipelineState.h"

namespace Papaya
{

  RenderApi::API Renderer::s_Api = RenderApi::API::OpenGL;
  glm::mat4 Renderer::s_ViewProjection = glm::mat4(1.0f);

  void Renderer::OnInit()
  {
    RenderCommand::OnInit();
    Renderer2D::OnInit();
  }

  void Renderer::OnTerminate()
  {
    RenderCommand::OnTerminate();
    Renderer2D::OnTerminate();
  }

  void Renderer::Begin(const OrthographicCamera &camera)
  {
    s_ViewProjection = camera.GetViewProjectionMatrix();
  }

  void Renderer::Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                        const Ref<PipelineState> pipelineState,
                        const Ref<Buffer> &indexBuffer,
                        const glm::mat4 &transform)
  {
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->Bind();
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->SetMat4("u_Camera", s_ViewProjection);
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->SetMat4("u_Transform", transform);
    RenderCommand::DrawIndexed(vertexBuffers, pipelineState, indexBuffer);
  }

  void Renderer::Submit(const Ref<Buffer> &vertexBuffer,
                        const Ref<PipelineState> pipelineState,
                        const Ref<Buffer> &indexBuffer,
                        const glm::mat4 &transform)
  {
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->Bind();
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->SetMat4("u_Camera", s_ViewProjection);
    std::static_pointer_cast<OpenGLPipelineState>(pipelineState)->m_Shader->SetMat4("u_Transform", transform);
    RenderCommand::DrawIndexed({vertexBuffer}, pipelineState, indexBuffer);
  }

  void Renderer::End()
  {
  }

} // namespace Papaya