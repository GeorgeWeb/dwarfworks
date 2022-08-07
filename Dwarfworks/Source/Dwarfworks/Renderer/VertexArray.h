#ifndef GRAPHICS_VERTEX_ARRAY_H
#define GRAPHICS_VERTEX_ARRAY_H

#include "Dwarfworks/Renderer/Buffer.h"

namespace Dwarfworks
{
class ENGINE_API VertexArray
{
  public:
    virtual ~VertexArray() {}

    virtual void Bind() const   = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)    = 0;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual Ref<IndexBuffer>                      GetIndexBuffer() const   = 0;

    static Ref<VertexArray> Create();
};

} // namespace Dwarfworks

#endif // GRAPHICS_VERTEX_ARRAY_H
