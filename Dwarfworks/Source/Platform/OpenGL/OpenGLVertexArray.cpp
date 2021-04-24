// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "Dwarfworks/Graphics/RendererAPI.h"

#include "OpenGLVertexArray.h"

namespace Dwarfworks
{
// Temporary
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case Dwarfworks::ShaderDataType::Float: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Float2: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Float3: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Float4: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Mat3: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Mat4: return GL_FLOAT;
        case Dwarfworks::ShaderDataType::Int: return GL_INT;
        case Dwarfworks::ShaderDataType::Int2: return GL_INT;
        case Dwarfworks::ShaderDataType::Int3: return GL_INT;
        case Dwarfworks::ShaderDataType::Int4: return GL_INT;
        case Dwarfworks::ShaderDataType::Bool: return GL_BOOL;
    }

    DW_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    if (GLAD_GL_VERSION_4_5)
    {
        glCreateVertexArrays(1, &m_RendererId);
    }
    else
    {
        glGenVertexArrays(1, &m_RendererId);
    }
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererId);
}

void OpenGLVertexArray::Unbind() const
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
        if (GLAD_GL_VERSION_4_5)
        {
            glEnableVertexArrayAttrib(m_RendererId, index);
        }
        else
        {
            glEnableVertexAttribArray(index);
        }
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

} // namespace Dwarfworks
