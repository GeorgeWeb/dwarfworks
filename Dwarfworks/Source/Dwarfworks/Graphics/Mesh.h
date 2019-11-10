#ifndef GRAPHICS_MESH_H_
#define GRAPHICS_MESH_H_

// #include "Dwarfworks/Core/Core.h"
// #include "Dwarfworks/Graphics/Material.h"
// #include "Dwarfworks/Graphics/VertexArray.h"

namespace Dwarfworks {
#if 0
class DW_API Mesh {
 public:
  Mesh() = default;
  // ...
  explicit Mesh(const Ref<VertexArray> vertexArray)
      : m_VertexArray(vertexArray) {}
  // ...
  Mesh(const Ref<VertexArray> vertexArray,
       const Ref<MaterialInstance>& materialInstance)
      : m_VertexArray(vertexArray), m_MaterialInstance(materialInstance) {}

  inline const Ref<VertexArray>& GetVertexArray() { return m_VertexArray; }
  inline const Ref<MaterialInstance>& GetMaterialInstance() {
    return m_MaterialInstance;
  }

  inline void SetMaterial(const Ref<MaterialInstance>& materialInstance) {
    m_MaterialInstance = materialInstance;
  }

 private:
  Ref<VertexArray> m_VertexArray;
  Ref<MaterialInstance> m_MaterialInstance;
};
#endif
}  // namespace Dwarfworks

#endif  // GRAPHICS_MESH_H_
