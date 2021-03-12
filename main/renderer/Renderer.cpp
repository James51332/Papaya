#include "Renderer.h"

#include "RenderCommand.h"
#include "ImGuiRenderer.h"
#include "Renderer2D.h"

namespace Papaya
{

  RenderApi::API Renderer::s_Api = RenderApi::API::OpenGL;
  glm::mat4 Renderer::s_ViewProjection = glm::mat4(1.0f);

  void Renderer::OnInit()
  {
    RenderCommand::OnInit();
    Renderer2D::OnInit();
    ImGuiRenderer::OnInit();
  }

  void Renderer::OnTerminate()
  {
    RenderCommand::OnTerminate();
    Renderer2D::OnTerminate();
    ImGuiRenderer::OnTerminate();
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
    pipelineState->GetShader()->Bind();
    pipelineState->GetShader()->SetMat4("u_Camera", s_ViewProjection);
    pipelineState->GetShader()->SetMat4("u_Transform", transform);
      
    RenderCommand::DrawIndexed(vertexBuffers, pipelineState, indexBuffer);
  }

  void Renderer::Submit(const Ref<Buffer> &vertexBuffer,
                        const Ref<PipelineState> pipelineState,
                        const Ref<Buffer> &indexBuffer,
                        const glm::mat4 &transform)
  {
    pipelineState->GetShader()->Bind();
    pipelineState->GetShader()->SetMat4("u_Camera", s_ViewProjection);
    pipelineState->GetShader()->SetMat4("u_Transform", transform);
    RenderCommand::DrawIndexed({vertexBuffer}, pipelineState, indexBuffer);
  }

  void Renderer::End()
  {
  }

} // namespace Papaya
