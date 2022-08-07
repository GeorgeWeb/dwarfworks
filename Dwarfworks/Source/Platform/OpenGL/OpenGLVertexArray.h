#ifndef PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H
#define PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H

#include "Dwarfworks/Renderer/VertexArray.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLVertexArray final : public VertexArray
{
  public:
    OpenGLVertexArray();

    ~OpenGLVertexArray() override final = default;

    void Bind() const override final;
    void Unbind() const override final;

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override final;
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override final;

    const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override final { return m_VertexBuffers; }
    Ref<IndexBuffer>                      GetIndexBuffer() const override final { return m_IndexBuffer; }

  private:
    std::uint32_t                  m_RendererId {0};
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer>               m_IndexBuffer;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_VERTEX_ARRAY_H
