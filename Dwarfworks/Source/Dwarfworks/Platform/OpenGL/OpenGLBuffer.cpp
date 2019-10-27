// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "OpenGLBuffer.h"

namespace Dwarfworks {

// OpenGL Vertex Buffer

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
  glCreateBuffers(1, &m_RendererId);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererId); }

void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// OpenGL Index Buffer

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count) {
  glCreateBuffers(1, &m_RendererId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_RendererId); }

void OpenGLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void OpenGLIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace Dwarfworks
