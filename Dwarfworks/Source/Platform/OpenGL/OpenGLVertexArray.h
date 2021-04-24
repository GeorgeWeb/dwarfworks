#ifndef PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_
#define PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_

#include "Dwarfworks/Graphics/VertexArray.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray() override = default;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
    virtual const Ref<IndexBuffer>&               GetIndexBuffer() const override { return m_IndexBuffer; }

  private:
    uint32_t                       m_RendererId;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer>               m_IndexBuffer;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H_
