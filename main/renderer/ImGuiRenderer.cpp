#include "ImGuiRenderer.h"

#include "main/core/Game.h"

#include "main/renderer/BufferLayout.h"
#include "main/renderer/Buffer.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Texture.h"
#include "main/renderer/PipelineState.h"
#include "main/renderer/RenderCommand.h"

#include "main/utils/String.h"
#include "main/utils/Memory.h"

#include <imgui/imgui.h>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

	struct ImGuiRenderData {
        Ref<Buffer> ImGuiVertexBuffer;
        Ref<Buffer> ImGuiIndexBuffer;
        Ref<PipelineState> ImGuiPipelineState;
        
		Ref<Texture2D> ImGuiTexture;
	};

	static ImGuiRenderData s_Data;

	void ImGuiRenderer::OnInit()
	{
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        
		ImGuiIO& io = ImGui::GetIO();
		io.BackendRendererName = "Papaya Renderer";
		io.BackendPlatformName = "Papaya Engine";
        
        io.DisplaySize.x = Game::Get()->GetWindow()->GetAttribs().Width;
        io.DisplaySize.y = Game::Get()->GetWindow()->GetAttribs().Height;

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
        #version 410 core
        
        layout (location = 0) out vec4 FragColor;
        
        in vec2 v_UV;
        in vec4 v_Color;
        
        uniform sampler2D u_Texture;
        
        void main()
        {
            FragColor = v_Color * texture(u_Texture, v_UV.st);
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

        unsigned char* pixels;
        int width, height;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
        s_Data.ImGuiTexture = Texture2D::Create(pixels, width, height, ChannelType::RGBA);
        // TODO: Load as RGBA 32-bit (75% of the memory is wasted, but default font
        // is so small) because it is more likely to be compatible
        // with user's existing shaders. If your ImTextureId represent a
        // higher-level concept than just a GL texture id, consider calling
        // GetTexDataAsAlpha8() instead to save on GPU memory.
	}

	void ImGuiRenderer::Flush()
	{
		ImDrawData* draw_data = ImGui::GetDrawData();

		int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
		int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
		if (fb_width <= 0 || fb_height <= 0)
			return;

		ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
		ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

        float L = draw_data->DisplayPos.x;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
        float T = draw_data->DisplayPos.y;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

        glm::mat4 ortho = glm::ortho(L, R, B, T);

        s_Data.ImGuiPipelineState->GetShader()->Bind();
        s_Data.ImGuiPipelineState->GetShader()->SetInt("u_Texture", 0);
        s_Data.ImGuiPipelineState->GetShader()->SetMat4("u_Projection", ortho);

		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];

			s_Data.ImGuiVertexBuffer->Reset(cmd_list->VtxBuffer.Data,
				cmd_list->VtxBuffer.Size * sizeof(ImDrawVert),
				BufferType::Vertex,
				BufferUsage::Stream);

			s_Data.ImGuiIndexBuffer->Reset(cmd_list->IdxBuffer.Data,
				cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx),
				BufferType::Index,
				BufferUsage::Stream);

			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
			{
				const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

                ImVec4 clip_rect;
                clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

                if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                {
                    s_Data.ImGuiTexture->Bind();
                        
                    RenderCommand::SetIndexSize(sizeof(ImDrawIdx));
                    RenderCommand::SetIndexOffset(pcmd->IdxOffset * sizeof(ImDrawIdx));
                    RenderCommand::SetElementCount(pcmd->ElemCount);
                    RenderCommand::DrawIndexed({ s_Data.ImGuiVertexBuffer }, s_Data.ImGuiPipelineState, s_Data.ImGuiIndexBuffer);
                }
			}
		}
	}

    void ImGuiRenderer::OnTerminate()
    {
    
    }
} // namespace Papaya
