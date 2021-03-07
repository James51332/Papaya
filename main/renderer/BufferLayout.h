#pragma once

#include "main/core/Log.h"

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include <vector>
#include <initializer_list>

namespace Papaya
{

  enum class ShaderDataType
  {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
  };

  static uint32_t ShaderDataTypeSize(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
      return 4;
    case ShaderDataType::Float2:
      return 4 * 2;
    case ShaderDataType::Float3:
      return 4 * 3;
    case ShaderDataType::Float4:
      return 4 * 4;
    case ShaderDataType::Mat3:
      return 4 * 3 * 3;
    case ShaderDataType::Mat4:
      return 4 * 4 * 4;
    case ShaderDataType::Int:
      return 4;
    case ShaderDataType::Int2:
      return 4 * 2;
    case ShaderDataType::Int3:
      return 4 * 3;
    case ShaderDataType::Int4:
      return 4 * 4;
    case ShaderDataType::Bool:
      return 1;
    default:
      break;
    }

    PAPAYA_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

  struct BufferElement
  {
    String Name;
    ShaderDataType Type;
    uint32_t Size;
    size_t Offset;
    bool Normalized;

    BufferElement() = default;

    BufferElement(ShaderDataType type, const String &name, bool normalized = false)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}
  };

  class BufferLayout
  {
  public:
    BufferLayout() {}

    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_Elements(elements)
    {
      CalculateOffsetsAndStride();
    }

    uint32_t GetStride() const { return m_Stride; }
    const std::vector<BufferElement> &GetElements() const { return m_Elements; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

  private:
    void CalculateOffsetsAndStride()
    {
      size_t offset = 0;
      m_Stride = 0;

      for (auto &element : m_Elements)
      {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
      }
    }

    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride;
  };

  // Each Vertex Buffer gets one
  class VertexDescriptor
  {
  public:
    VertexDescriptor() = default;

    VertexDescriptor(BufferLayout layout)
        : m_Elements({layout}) {}

    VertexDescriptor(std::initializer_list<BufferLayout> elements)
        : m_Elements(elements) {}

    int GetCount() const { return static_cast<int>(m_Elements.size()); }
    const std::vector<BufferLayout> &GetElements() const { return m_Elements; }

    std::vector<BufferLayout>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferLayout>::iterator end() { return m_Elements.end(); }
    std::vector<BufferLayout>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferLayout>::const_iterator end() const { return m_Elements.end(); }

  private:
    std::vector<BufferLayout> m_Elements;
  };

} // namespace Papaya