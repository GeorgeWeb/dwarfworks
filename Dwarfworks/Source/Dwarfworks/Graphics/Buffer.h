#ifndef GRAPHICS_BUFFER_H_
#define GRAPHICS_BUFFER_H_

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks {

/// \class VertexBuffer
///
/// \brief Vertex Buffer interface.
///
/// \author Georg
/// \date 20/10/2019

class DW_API VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  static Scope<VertexBuffer> Create(float* vertices, uint32_t size);
};

/// \class IndexBuffer
///
/// \brief Index (Element) Buffer interface.
///
/// \author Georg
/// \date 20/10/2019

class DW_API IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual uint32_t GetCount() const = 0;

  static Scope<IndexBuffer> Create(uint32_t* indices, uint32_t count);
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_BUFFER_H_
