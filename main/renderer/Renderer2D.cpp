#include "Renderer2D.h"

#include "Buffer.h"
#include "BufferLayout.h"
#include "PipelineState.h"
#include "RenderCommand.h"

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <array>

// Based of TheCherno/Hazel's Renderer2D

namespace Papaya
{

  struct QuadVertex
  { // defines the layout of one vertex. An array of these is uploaded to the gpu
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
    float TilingFactor;
  };

  struct Renderer2DData // Stores the state of the renderer
  {
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 16;

    Ref<Buffer> QuadVertexBuffer;
    Ref<Buffer> QuadIndexBuffer;
    Ref<PipelineState> QuadPipelineState;

    uint32_t QuadIndexCount = 0;

    // This is the head of an array of vertices.
    QuadVertex *QuadVertexBufferBase = nullptr;

    // This pointer moves as we add quads to the batch so
    // we can determine the size of the data to send to the gpu
    QuadVertex *QuadVertexBufferPtr = nullptr;

    Ref<Texture2D> WhiteTexture;

    std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
    uint32_t TextureIndex = 1; // 0 = WhiteTexture

    glm::vec4 QuadVertexPositions[4];
  };

  static Renderer2DData s_Data;

  void Renderer2D::OnInit()
  {
    // Create Vertex Buffer
    s_Data.QuadVertexBuffer = Buffer::Create(nullptr,
                                             sizeof(QuadVertex) * s_Data.MaxVertices,
                                             BufferType::Vertex,
                                             BufferUsage::Dynamic);

    // Create Index Buffer Data
    uint32_t *quadIndices = new uint32_t[s_Data.MaxIndices];
    uint32_t offset = 0; // transforms are baked into data so we need to offset indices to vertices later in data
    for (int i = 0; i < s_Data.MaxIndices; i += 6)
    {
      quadIndices[i + 0] = offset + 0;
      quadIndices[i + 1] = offset + 1;
      quadIndices[i + 2] = offset + 2;

      quadIndices[i + 3] = offset + 0;
      quadIndices[i + 4] = offset + 2;
      quadIndices[i + 5] = offset + 3;

      offset += 4; // increase four vertices for every six indices
    }

    // Create Index Buffer
    s_Data.QuadIndexBuffer = Buffer::Create(quadIndices,
                                            sizeof(uint32_t) * s_Data.MaxIndices,
                                            BufferType::Index,
                                            BufferUsage::Immutable);

    // Free Index Buffer Data
    delete[] quadIndices;

    // Create Vertex Data Array
    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

    // Create Shader (TODO: Figure out how we want to store shaders [e.g. files, in executable, strings, etc.])
    String vs = R"(
    #version 410 core

    layout (location = 0) in vec3 a_Pos;  
    layout (location = 1) in vec4 a_Color;  
    layout (location = 2) in vec2 a_TexCoord;  
    layout (location = 3) in float a_TexIndex;  
    layout (location = 4) in float a_TilingFactor;

    uniform mat4 u_ViewProjection;

    out vec4 v_Color;
    out vec2 v_TexCoord;
    flat out float v_TexIndex;
    out float v_TilingFactor;

    void main() {
      v_Color = a_Color;
      v_TexCoord = a_TexCoord;
      v_TexIndex = a_TexIndex;
      v_TilingFactor = a_TilingFactor;
      gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);
    })";

    String fs = R"(
    #version 410 core

    layout (location = 0) out vec4 FragColor;

    in vec4 v_Color;
    in vec2 v_TexCoord;
    flat in float v_TexIndex;
    in float v_TilingFactor;

    uniform sampler2D u_Textures[16];

    void main() {
      FragColor = v_Color * texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor);
    })";

    Ref<Shader> shader = Shader::Create(vs, fs);

    // Set the layout of a vertex
    VertexDescriptor layout = {{{ShaderDataType::Float3, "a_Pos"},
                                {ShaderDataType::Float4, "a_Color"},
                                {ShaderDataType::Float2, "a_TexCoord"},
                                {ShaderDataType::Float, "a_TexIndex"},
                                {ShaderDataType::Float, "a_TilingFactor"}}};

    // Create the pipeline state using the shader and layout
    s_Data.QuadPipelineState = PipelineState::Create({shader, layout});

    int samplers[s_Data.MaxTextureSlots];
    for (int i = 0; i < s_Data.MaxTextureSlots; ++i)
      samplers[i] = i;

    s_Data.QuadPipelineState->GetShader()->Bind();
    s_Data.QuadPipelineState->GetShader()->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);  

    s_Data.WhiteTexture = Texture2D::Create("tests/assets/textures/checkboard.png");
    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    // Create basic quad vertices that we can later sample from
    s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
  }

  void Renderer2D::OnTerminate()
  {
    // Delete Vertex Data Array
    delete[] s_Data.QuadVertexBufferBase;
  }

  void Renderer2D::BeginScene(const OrthographicCamera &camera)
  {
    s_Data.QuadPipelineState->GetShader()->Bind();
    s_Data.QuadPipelineState->GetShader()->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    StartBatch();
  }

  void Renderer2D::EndScene()
  {
    Flush();
  }

  void Renderer2D::StartBatch()
  {
    // Reset the vertex buffer pointer for the new batch
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.QuadIndexCount = 0;

    // Reset the texture index
    s_Data.TextureIndex = 1; // 0 = White Texture
  }

  void Renderer2D::Flush()
  {
    if (s_Data.QuadIndexCount == 0)
      return; // Nothing to draw

    // Determine how many much of the vertex array we need to set.
    uint32_t dataSize = static_cast<uint32_t>(s_Data.QuadVertexBufferPtr - s_Data.QuadVertexBufferBase) * sizeof(QuadVertex);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize); // Send the determined amount of data to the gpu

    // Bind Pipeline State
    s_Data.QuadPipelineState->Bind();

    // Bind Textures
    for (int i = 0; i < s_Data.TextureIndex; ++i)
      s_Data.TextureSlots[i]->Bind(i);

    RenderCommand::SetIndexSize(sizeof(uint32_t));
    RenderCommand::SetIndexOffset(0);
    RenderCommand::SetElementCount(0);
    RenderCommand::DrawIndexed({ s_Data.QuadVertexBuffer }, s_Data.QuadPipelineState, s_Data.QuadIndexBuffer);
  }

  void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
  {
    constexpr size_t quadVertexCount = 4;
    const float textureIndex = 0.0f; // White Texture
    constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    const float tilingFactor = 1.0f;

    if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
    {
      Flush();
      StartBatch();
    }

    for (size_t i = 0; i < quadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++; // On the next iteration/draw we will use the next vertex
    }

    s_Data.QuadIndexCount += 6;
  }

  void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    constexpr size_t quadVertexCount = 4;
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
    {
      Flush();
      StartBatch();
    }

    float textureIndex = 0.0f;
    for (int i = 0; i < s_Data.TextureIndex; i++)
    { // check if texture is already used in batch
      if (*s_Data.TextureSlots[i] == *texture)
      {
        textureIndex = static_cast<float>(i);
        break;
      }
    }

    if (textureIndex == 0.0f)
    {
      if (s_Data.TextureIndex >= s_Data.MaxTextureSlots)
      {
        Flush();
        StartBatch();
      }

      textureIndex = s_Data.TextureIndex;
      s_Data.TextureSlots[s_Data.TextureIndex] = texture;
      s_Data.TextureIndex++;
    }

    for (int i = 0; i < quadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = tintColor;
      s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++; // On the next iteration/draw we will use the next vertex
    }

    s_Data.QuadIndexCount += 6;
  }

} // namespace Papaya
