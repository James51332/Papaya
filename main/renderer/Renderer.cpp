#include "Renderer.h"

#include "RenderCommand.h"

namespace Papaya
{

    RenderApi::API Renderer::s_Api = RenderApi::API::OpenGL;

    void Renderer::OnInit()
    {
        RenderCommand::OnInit();
    }

    void Renderer::OnTerminate()
    {
        RenderCommand::OnTerminate();
    }

    void Renderer::Begin()
    {
    }

    void Renderer::Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                          const Ref<PipelineState> pipelineState,
                          const Ref<Buffer> &indexBuffer)
    {
        RenderCommand::DrawIndexed(vertexBuffers, pipelineState, indexBuffer);
    }

    void Renderer::Submit(const Ref<Buffer>& vertexBuffer,
                          const Ref<PipelineState> pipelineState,
                          const Ref<Buffer>& indexBuffer)
    {
        RenderCommand::DrawIndexed({ vertexBuffer }, pipelineState, indexBuffer);
    }

    void Renderer::End()
    {
    }

} // namespace Papaya