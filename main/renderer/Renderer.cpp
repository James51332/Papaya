#include "Renderer.h"

#include "RenderCommand.h"

namespace Papaya
{
    
RenderApi::API Renderer::s_Api = RenderApi::API::OpenGL;

void Renderer::OnInit() { 
    RenderCommand::OnInit();
}

void Renderer::OnTerminate() { 
    RenderCommand::OnTerminate();
}

void Renderer::Begin() { 

}

void Renderer::Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                                  const BufferLayout &layout,
                                  const Ref<Buffer> &indexBuffer,
                                  const Ref<Shader> &shader)
{
    RenderCommand::DrawIndexed(vertexBuffers, layout, indexBuffer, shader);
}

void Renderer::End() { 

}

} // namespace Papaya