#include "imgui_impl_opengl3.h"

#include "main/renderer/BufferLayout.h"
#include "main/renderer/Buffer.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Texture.h"
#include "main/renderer/PipelineState.h"
#include "main/renderer/RenderCommand.h"

#include "main/utils/String.h"
#include "main/utils/Memory.h"

#include <stdio.h>
#include <imgui/imgui.h>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "platform/opengl/OpenGLLoader.h"

namespace Papaya
{

	struct ImGuiRenderData {
		Ref<Texture2D> ImGuiTexture;
		Ref<PipelineState> ImGuiPipelineState;

		Ref<Buffer> ImGuiVertexBuffer;
		Ref<Buffer> ImGuiIndexBuffer;
	};

	static ImGuiRenderData s_Data;

	static GLuint g_GlVersion = 0;            // Extracted at runtime using GL_MAJOR_VERSION, GL_MINOR_VERSION queries (e.g. 320 for GL 3.2)
	static char g_GlslVersionString[32] = ""; // Specified by user or detected based on compile time GL settings.
	static GLuint g_FontTexture = 0;
	static GLuint g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
	static GLint g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;                                 // Uniforms location
	static GLuint g_AttribLocationVtxPos = 0, g_AttribLocationVtxUV = 0, g_AttribLocationVtxColor = 0; // Vertex attributes location
	static unsigned int g_VboHandle = 0, g_ElementsHandle = 0;

	// Functions
	bool ImGui_Init()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.BackendRendererName = "Papaya Renderer";
		io.BackendPlatformName = "Papaya Engine";

		ImGui_CreateDeviceObjects();

		return true;
	}

	void ImGui_Shutdown()
	{
		ImGui_DestroyDeviceObjects();
	}

	void ImGui_NewFrame()
	{
	}

	static void ImGui_SetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object)
	{
		// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glDisable(GL_CULL_FACE);
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_STENCIL_TEST);
		//glEnable(GL_SCISSOR_TEST);

		float L = draw_data->DisplayPos.x;
		float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
		float T = draw_data->DisplayPos.y;
		float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

		glm::mat4 ortho = glm::ortho(L, R, B, T);

		s_Data.ImGuiPipelineState->GetShader()->Bind();
		s_Data.ImGuiPipelineState->GetShader()->SetInt("Texture", 0);
		s_Data.ImGuiPipelineState->GetShader()->SetMat4("ProjMtx", ortho);

		//glBindVertexArray(vertex_array_object);
		//s_Data.ImGuiVertexBuffer->Bind();
		//s_Data.ImGuiIndexBuffer->Bind();
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)0);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)8);
		//glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)16);
	}

	void ImGui_Render()
	{
		ImDrawData* draw_data = ImGui::GetDrawData();

		int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
		int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
		if (fb_width <= 0 || fb_height <= 0)
			return;

		ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
		ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

		ImGui_SetupRenderState(draw_data, fb_width, fb_height, 0);

		// Render command lists
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];

			// Upload vertex/index buffers
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
				if (pcmd->UserCallback != NULL)
				{
					// User callback, registered via ImDrawList::AddCallback()
					// (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
					if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
						ImGui_SetupRenderState(draw_data, fb_width, fb_height, 0);
					else
						pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					// Project scissor/clipping rectangles into framebuffer space
					ImVec4 clip_rect;
					clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
					clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
					clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
					clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

					if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
					{
						// Bind texture, Draw
						s_Data.ImGuiTexture->Bind();
						glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)));
					
						RenderCommand::SetIndexSize(sizeof(ImDrawIdx));
						RenderCommand::SetIndexOffset(pcmd->IdxOffset * sizeof(ImDrawIdx));
						RenderCommand::SetElementCount(pcmd->ElemCount);

						RenderCommand::DrawIndexed({ s_Data.ImGuiVertexBuffer }, s_Data.ImGuiPipelineState, s_Data.ImGuiIndexBuffer);
					}
				}
			}
		}
	}


	bool ImGui_CreateDeviceObjects()
	{
		String vertexSrc = R"(
        #version 410 core

        layout (location = 0) in vec2 Position;
        layout (location = 1) in vec2 UV;
        layout (location = 2) in vec4 Color;
        uniform mat4 ProjMtx;
        out vec2 Frag_UV;
        out vec4 Frag_Color;
        void main()
        {
            Frag_UV = UV;
            Frag_Color = Color;
            gl_Position = ProjMtx * vec4(Position.xy,0,1);
        })";

		String fragmentSrc = R"(
        #version 410 core
        
        in vec2 Frag_UV;
        in vec4 Frag_Color;
        uniform sampler2D Texture;
        layout (location = 0) out vec4 Out_Color;
        void main()
        {
            Out_Color = Frag_Color * texture(Texture, Frag_UV.st);
        })";

		Ref<Shader> shader = Shader::Create(vertexSrc, fragmentSrc);

		VertexDescriptor layout = {{
			{ ShaderDataType::Float2, "Position" },
			{ ShaderDataType::Float2, "UV" },
			{ ShaderDataType::Byte, "Color", true } 
		}};

		s_Data.ImGuiPipelineState = PipelineState::Create({ shader, layout });

		// Create buffers
		s_Data.ImGuiVertexBuffer = Buffer::Create();
		s_Data.ImGuiIndexBuffer = Buffer::Create();

		ImGuiIO& io = ImGui::GetIO();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height); // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
		s_Data.ImGuiTexture = Texture2D::Create(pixels, width, height, ChannelType::RGBA);

		return true;
	}

	void ImGui_DestroyDeviceObjects()
	{
		if (g_VboHandle)
		{
			glDeleteBuffers(1, &g_VboHandle);
			g_VboHandle = 0;
		}
		if (g_ElementsHandle)
		{
			glDeleteBuffers(1, &g_ElementsHandle);
			g_ElementsHandle = 0;
		}
		//if (g_ShaderHandle && g_VertHandle)
		//{
		//    // glDetachShader(g_ShaderHandle, g_VertHandle);
		//}
		//if (g_ShaderHandle && g_FragHandle)
		//{
		//    // glDetachShader(g_ShaderHandle, g_FragHandle);
		//}
		//if (g_VertHandle)
		//{
		//    glDeleteShader(g_VertHandle);
		//    g_VertHandle = 0;
		//}
		//if (g_FragHandle)
		//{
		//    glDeleteShader(g_FragHandle);
		//    g_FragHandle = 0;
		//}
		//if (g_ShaderHandle)
		//{
		//    //glDeleteProgram(g_ShaderHandle);
		//    g_ShaderHandle = 0;
		//}
	}
}