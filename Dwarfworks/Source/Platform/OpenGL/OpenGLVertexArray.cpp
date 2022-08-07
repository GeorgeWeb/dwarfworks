// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Renderer/RendererAPI.h"

#include "OpenGLVertexArray.h"
#include "OpenGLUtil.h"

using namespace Dwarfworks;

// Temporary
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        default:
            // fall-through
        case ShaderDataType::None: break;
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
    }

    DW_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() : m_IndexBuffer(IndexBuffer::Create(nullptr, 0))
{
    OpenGL::CreateVertexArrays(1, &m_RendererId);
}

inline void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererId);
}

inline void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    DW_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererId);
    vertexBuffer->Bind();

    uint32_t    index  = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
        OpenGL::EnableVertexArrayAttrib(m_RendererId, index);
        glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              reinterpret_cast<const void*>(element.Offset));
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererId);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}
