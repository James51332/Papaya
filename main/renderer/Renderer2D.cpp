#include "Renderer2D.h"

#include "Buffer.h"
#include "PipelineState.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <array>

namespace Papaya
{

  // Most of this renderer is from TheCherno/Hazel with slight modifications to use our API

  struct QuadVertex
  {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
    float TilingFactor;
  };

  struct Renderer2DData
  {
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

    Ref<Buffer> QuadVertexBuffer;
    Ref<Buffer> QuadIndexBuffer;
    Ref<PipelineState> QuadPipelineState;
    Ref<Texture2D> WhiteTexture; // TODO: White Texture (Loads Checkboard right now)

    uint32_t QuadIndexCount = 0;
    QuadVertex *QuadVertexBufferBase = nullptr;
    QuadVertex *QuadVertexBufferPtr = nullptr;

    std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
    uint32_t TextureSlotIndex = 1; // 0 = white texture

    glm::vec4 QuadVertexPositions[4];
  };

  static Renderer2DData s_Data;

  void Renderer2D::OnInit()
  {
    s_Data.QuadVertexBuffer = Buffer::Create(nullptr,
                                             sizeof(s_Data.MaxVertices) * sizeof(QuadVertex),
                                             BufferType::Vertex,
                                             BufferUsage::Dynamic);

    uint32_t *quadIndices = new uint32_t[s_Data.MaxIndices];

    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
    {
      quadIndices[i + 0] = offset + 0;
      quadIndices[i + 1] = offset + 1;
      quadIndices[i + 2] = offset + 2;

      quadIndices[i + 3] = offset + 2;
      quadIndices[i + 4] = offset + 3;
      quadIndices[i + 5] = offset + 0;

      offset += 4;
    }

    s_Data.QuadIndexBuffer = Buffer::Create(quadIndices,
                                            sizeof(quadIndices) * sizeof(uint32_t),
                                            BufferType::Index,
                                            BufferUsage::Dynamic);
    delete[] quadIndices;

    // TODO: Put shader into file or at least a better spot
    String textureShaderVertex = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out flat float v_TexIndex;
out float v_TilingFactor;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
})";

    String textureShaderFragment = R"(
      #version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in flat float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
	vec4 texColor = v_Color;
	switch(int(v_TexIndex))
	{
		case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
		case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
		case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
		case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
		case 4: texColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
		case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
		case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
		case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
		case 8: texColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
		case 9: texColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
		case 16: texColor *= texture(u_Textures[16], v_TexCoord * v_TilingFactor); break;
		case 17: texColor *= texture(u_Textures[17], v_TexCoord * v_TilingFactor); break;
		case 18: texColor *= texture(u_Textures[18], v_TexCoord * v_TilingFactor); break;
		case 19: texColor *= texture(u_Textures[19], v_TexCoord * v_TilingFactor); break;
		case 20: texColor *= texture(u_Textures[20], v_TexCoord * v_TilingFactor); break;
		case 21: texColor *= texture(u_Textures[21], v_TexCoord * v_TilingFactor); break;
		case 22: texColor *= texture(u_Textures[22], v_TexCoord * v_TilingFactor); break;
		case 23: texColor *= texture(u_Textures[23], v_TexCoord * v_TilingFactor); break;
		case 24: texColor *= texture(u_Textures[24], v_TexCoord * v_TilingFactor); break;
		case 25: texColor *= texture(u_Textures[25], v_TexCoord * v_TilingFactor); break;
		case 26: texColor *= texture(u_Textures[26], v_TexCoord * v_TilingFactor); break;
		case 27: texColor *= texture(u_Textures[27], v_TexCoord * v_TilingFactor); break;
		case 28: texColor *= texture(u_Textures[28], v_TexCoord * v_TilingFactor); break;
		case 29: texColor *= texture(u_Textures[29], v_TexCoord * v_TilingFactor); break;
		case 30: texColor *= texture(u_Textures[30], v_TexCoord * v_TilingFactor); break;
		case 31: texColor *= texture(u_Textures[31], v_TexCoord * v_TilingFactor); break;
	}
	color = texColor;
})";

    int32_t samplers[s_Data.MaxTextureSlots];
    for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
      samplers[i] = i;

    s_Data.WhiteTexture = Texture2D::Create("tests/assets/textures/Checkboard.png");

    PipelineStateDesc desc;
    desc.Shader = Shader::Create(textureShaderVertex, textureShaderFragment);
    desc.Layout = {{{ShaderDataType::Float3, "a_Position"},
                    {ShaderDataType::Float4, "a_Color"},
                    {ShaderDataType::Float2, "a_TexCoord"},
                    {ShaderDataType::Float, "a_TexIndex"},
                    {ShaderDataType::Float, "a_TilingFactor"}}};
    s_Data.QuadPipelineState = PipelineState::Create(desc);

    s_Data.QuadPipelineState->GetShader()->Bind();
    s_Data.QuadPipelineState->GetShader()->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
  }

  void Renderer2D::OnTerminate()
  {
  }

  void Renderer2D::BeginScene(const OrthographicCamera &camera)
  {
    s_Data.QuadPipelineState->GetShader()->Bind();
    s_Data.QuadPipelineState->GetShader()->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
  }

  void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
  {
    constexpr size_t quadVertexCount = 4;
    const float textureIndex = 0.0f; // White Texture
    constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    const float tilingFactor = 1.0f;

    // if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
    //   NextBatch();

    for (size_t i = 0; i < quadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
  }

  void Renderer2D::EndScene()
  {

    if (s_Data.QuadIndexCount == 0)
      return; // Nothing to draw

    uint32_t dataSize = (uint32_t)((uint8_t *)s_Data.QuadVertexBufferPtr - (uint8_t *)s_Data.QuadVertexBufferBase);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    // Bind textures
    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
      s_Data.TextureSlots[i]->Bind(i);

    RenderCommand::DrawIndexed({s_Data.QuadVertexBuffer}, s_Data.QuadPipelineState, s_Data.QuadIndexBuffer);
  }

} // namespace Papaya
