#ifndef PLATFORM_OPENGL_OPENGL_BUFFER_H_
#define PLATFORM_OPENGL_OPENGL_BUFFER_H_

#include "Dwarfworks/Graphics/Buffer.h"

namespace Dwarfworks {

class DW_API OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, uint32_t size);
  virtual ~OpenGLVertexBuffer() override;

  OpenGLVertexBuffer(const OpenGLVertexBuffer&) = default;
  OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = default;
  OpenGLVertexBuffer(OpenGLVertexBuffer&&) = default;
  OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&&) = default;

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual const BufferLayout& GetLayout() const override { return m_Layout; }
  virtual void SetLayout(const BufferLayout& layout) override {
    m_Layout = layout;
  }

 private:
  uint32_t m_RendererId;
  BufferLayout m_Layout;
};

class DW_API OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
  ~OpenGLIndexBuffer() override;

  virtual void Bind() const override;
  virtual void Unbind() const override;

  uint32_t GetCount() const override { return m_Count; }

 private:
  uint32_t m_RendererId;
  uint32_t m_Count;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_BUFFER_H_
