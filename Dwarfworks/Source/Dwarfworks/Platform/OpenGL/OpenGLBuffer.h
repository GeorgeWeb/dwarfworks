#ifndef PLATFORM_OPENGL_OPENGL_BUFFER_H_
#define PLATFORM_OPENGL_OPENGL_BUFFER_H_

#include "Dwarfworks/Graphics/Buffer.h"

namespace Dwarfworks {

class DW_API OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, uint32_t size);
  ~OpenGLVertexBuffer() override;

  void Bind() const override;
  void Unbind() const override;

 private:
  uint32_t m_RendererId;
};

class DW_API OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
  ~OpenGLIndexBuffer() override;

  void Bind() const override;
  void Unbind() const override;

  uint32_t GetCount() const override { return m_Count; }

 private:
  uint32_t m_RendererId;
  uint32_t m_Count;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_BUFFER_H_
