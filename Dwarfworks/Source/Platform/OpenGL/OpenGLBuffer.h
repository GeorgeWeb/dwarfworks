#ifndef PLATFORM_OPENGL_OPENGL_BUFFER_H
#define PLATFORM_OPENGL_OPENGL_BUFFER_H

#include "Dwarfworks/Renderer/Buffer.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLVertexBuffer final : public VertexBuffer
{
  public:
    OpenGLVertexBuffer() = default;
    OpenGLVertexBuffer(float* vertices, uint32_t size);

    ~OpenGLVertexBuffer() override final;

    void Bind() const override final;
    void Unbind() const override final;

    const BufferLayout& GetLayout() const override final { return m_Layout; }
    void                SetLayout(const BufferLayout& layout) override final { m_Layout = layout; }

  private:
    std::uint32_t m_RendererId {0};
    BufferLayout  m_Layout;
};

class ENGINE_API OpenGLIndexBuffer final : public IndexBuffer
{
  public:
    OpenGLIndexBuffer() = default;
    OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count);

    ~OpenGLIndexBuffer() override final;

    void Bind() const override final;
    void Unbind() const override final;

    std::uint32_t GetCount() const override final { return m_Count; }

  private:
    std::uint32_t m_RendererId {0};
    std::uint32_t m_Count;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_BUFFER_H
