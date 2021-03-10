

#include <imgui/imgui.h>
#include "imgui_impl_opengl3.h"

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"
#include "main/renderer/Texture.h"
#include "main/renderer/PipelineState.h"
#include "main/renderer/RenderCommand.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Papaya {

struct ImGuiRenderData {
    Ref<Texture2D> ImGuiFontTexture;

    Ref<Buffer> ImGuiVertexBuffer;
    Ref<Buffer> ImGuiIndexBuffer;

    Ref<PipelineState> ImGuiPipelineState;
};

static ImGuiRenderData s_Data;

bool ImGui_Init()
{
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "Papaya";

    ImGui_CreateDeviceObjects();

    return true;
}

void ImGui_ImplOpenGL3_Shutdown()
{
}

static void ImGui_SetupRenderState(ImDrawData* draw_data)
{   
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    glm::mat4 ortho = glm::ortho(L, R, B, T);

    s_Data.ImGuiPipelineState->GetShader()->Bind();
    s_Data.ImGuiPipelineState->GetShader()->SetInt("u_Texture", 0);
    s_Data.ImGuiPipelineState->GetShader()->SetMat4("u_Projection", ortho);
}

void ImGui_Render()
{
    ImDrawData* draw_data = ImGui::GetDrawData();
    
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    ImGui_SetupRenderState(draw_data);

    // Render command lists
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];

        // Upload vertex/index buffers
        s_Data.ImGuiVertexBuffer->Reset(cmd_list->VtxBuffer.Data,
                                        cmd_list->VtxBuffer.Size * (int)sizeof(ImDrawVert),
                                        BufferType::Vertex,
                                        BufferUsage::Stream);

        s_Data.ImGuiIndexBuffer->Reset(cmd_list->IdxBuffer.Data,
                                       cmd_list->IdxBuffer.Size * (int)sizeof(ImDrawIdx),
                                       BufferType::Index,
                                       BufferUsage::Stream);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != NULL)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_SetupRenderState(draw_data);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                s_Data.ImGuiFontTexture->Bind();
                
                RenderCommand::SetIndexSize(2);
                RenderCommand::SetIndexOffset(pcmd->IdxOffset * sizeof(ImDrawIdx));
                RenderCommand::DrawIndexed({ s_Data.ImGuiVertexBuffer}, s_Data.ImGuiPipelineState, s_Data.ImGuiIndexBuffer);
            }
        }
    }
}

bool ImGui_CreateFontsTexture()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible
    // with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider
    // calling GetTexDataAsAlpha8() instead to save on GPU memory.

    s_Data.ImGuiFontTexture = Texture2D::Create(pixels, width, height, ChannelType::RGBA);

    return true;
}

bool ImGui_CreateDeviceObjects()
{
    String vertexSrc = R"(
    #version 410 core
    
    layout (location = 0) in vec2 a_Pos;
    layout (location = 1) in vec2 a_UV;
    layout (location = 2) in vec4 a_Color;

    out vec2 v_UV;
    out vec4 v_Color;

    uniform mat4 u_Projection;

    void main()
    {
        v_UV = a_UV;
        v_Color = a_Color;
        gl_Position = u_Projection * vec4(a_Pos.xy, 0, 1);
    })";

    String fragmentSrc = R"(
    #version 410
    
    layout (location = 0) out vec4 Out_Color;

    in vec2 v_UV;
    in vec4 v_Color;

    uniform sampler2D u_Texture;

    void main()
    {
        Out_Color = v_Color * texture(u_Texture, v_UV.st);
    })";

    Ref<Shader> shader = Shader::Create(vertexSrc, fragmentSrc);

    VertexDescriptor layout = {{
        { ShaderDataType::Float2, "a_Pos" },
        { ShaderDataType::Float2, "a_UV" },
        { ShaderDataType::Byte, "a_Color", true }
    }};

    s_Data.ImGuiPipelineState = PipelineState::Create({ shader, layout });

    s_Data.ImGuiVertexBuffer = Buffer::Create();
    s_Data.ImGuiIndexBuffer = Buffer::Create();

    ImGui_CreateFontsTexture();

    return true;
}
} // namespace Papaya
