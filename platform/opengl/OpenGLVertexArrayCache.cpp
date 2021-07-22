#include "papayapch.h"
#include "OpenGLVertexArrayCache.h"
#include "OpenGLLoader.h"



#include "main/utils/Hash.h"

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

namespace Papaya
{

  std::unordered_map<std::size_t, Ref<OpenGLVertexArray>> OpenGLVertexArrayCache::s_Cache;

  static GLenum ShaderDataTypeToGLType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
      return GL_FLOAT;
    case ShaderDataType::Float2:
      return GL_FLOAT;
    case ShaderDataType::Float3:
      return GL_FLOAT;
    case ShaderDataType::Float4:
      return GL_FLOAT;
    case ShaderDataType::Mat3:
      return GL_FLOAT;
    case ShaderDataType::Mat4:
      return GL_FLOAT;
    case ShaderDataType::Int:
      return GL_INT;
    case ShaderDataType::Int2:
      return GL_INT;
    case ShaderDataType::Int3:
      return GL_INT;
    case ShaderDataType::Int4:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    case ShaderDataType::Byte:
      return GL_UNSIGNED_BYTE;
    default:
      break;
    }

    PAPAYA_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

  static std::size_t GenerateKey(const std::vector<Ref<Buffer>> &vertexBuffers,
                                 const VertexDescriptor &vd,
                                 const Ref<Buffer> &indexBuffer)
  {
    // TODO: This is the core of the cache system. We need to minimize the risk
    // of the same value for multiple models and also have a fast algorithm.
    // I'm marking this as TODO because it is potentially a fault that should
    // be looked into if there are flaws in OpenGL rendering.

    // The system that we'll use is highly inspired by DiligentEngine/DiligentCore's
    // VAOCacheKey system. They use code from the boost library to combine keys from
    // an unset number of values. This feels sufficiently unlikely that the same
    // key will be generated even though it's not impossible. (I think)

    std::size_t seed = 0;

    for (auto &vb : vertexBuffers)
      Papaya::HashCombine(seed, std::static_pointer_cast<OpenGLBuffer>(vb)->GetUniqueID()); // BufferID's start at 1000 and go up

    for (auto &layout : vd)
    {
      Papaya::HashCombine(seed, layout.GetStride());
      for (auto &element : layout)
      {
        Papaya::HashCombine(seed, element.Offset);
        Papaya::HashCombine(seed, element.Size);
      }
    }

    Papaya::HashCombine(seed, indexBuffer ? std::static_pointer_cast<OpenGLBuffer>(indexBuffer)->GetUniqueID() : 0); // This should almost always be included

    return seed;
  }

  OpenGLVertexArrayCache::~OpenGLVertexArrayCache()
  {
  }

  Ref<OpenGLVertexArray> OpenGLVertexArrayCache::GetVertexArray(const std::vector<Ref<Buffer>> &vertexBuffers,
                                                                const Ref<PipelineState> &pipelineState,
                                                                const Ref<Buffer> &indexBuffer)
  {
    VertexDescriptor layout = pipelineState->GetLayout();
      
    std::size_t key = GenerateKey(vertexBuffers, layout, indexBuffer);

    auto vao = s_Cache.find(key);
    if (vao != s_Cache.end())
    {
      return vao->second;
    }
    else
    {
        if (layout.GetCount() != vertexBuffers.size())
        {
            PAPAYA_WARN("Vertex Buffers and Pipeline State Layout don't have the same number of elements!");
        }

        
      // Create new VAO
      Ref<OpenGLVertexArray> vertexArray = CreateRef<OpenGLVertexArray>();

      for (auto &buffer : vertexBuffers)
      {
        vertexArray->SetVertexBuffer(buffer);
      }
        
      // Setting the vertex buffers binds the vao
      int buffer = 0;
      int index = 0;
      for (auto &bl : layout)
      {
        vertexBuffers[buffer]->Bind();
        buffer++;

        for (auto &element : bl)
        {
          bool normalizedByte = element.Normalized && (element.Type == ShaderDataType::Byte);
          glVertexAttribPointer(index,
                                normalizedByte ? 4 : element.Size / 4,
                                ShaderDataTypeToGLType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                bl.GetStride(),
                                (GLvoid *)element.Offset);
          glEnableVertexAttribArray(index);
          index++;
        }
      }

      vertexArray->SetIndexBuffer(indexBuffer);

      s_Cache.emplace(key, vertexArray);

      return vertexArray;
    }
  }

} // namespace Papaya
