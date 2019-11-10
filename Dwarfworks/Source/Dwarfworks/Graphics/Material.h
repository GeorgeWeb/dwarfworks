#ifndef GRAPHICS_MATERIAL_H_
#define GRAPHICS_MATERIAL_H_

// #include "Dwarfworks/Core/Core.h"
// #include "Dwarfworks/Graphics/Shader.h"
// #include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {
#if 0
class DW_API Material {
 public:
  explicit Material(const Ref<Shader>& shader);

  inline const Ref<Shader>& GetShader() { return m_Shader; }

  static Ref<Material> Create(const Ref<Shader>& shader);

  void Bind() const;

 private:
  Ref<Shader> m_Shader;
};

class DW_API MaterialInstance {
 public:
  explicit MaterialInstance(const Ref<Material>& material);

  inline const Ref<Material>& GetMaterial() { return m_Material; }

  void SetBool(std::string_view name, bool val) const;
  void SetInt(std::string_view name, int val) const;
  void SetFloat(std::string_view name, float val) const;
  void SetFloat2(std::string_view name, const glm::vec2& vec) const;
  void SetFloat3(std::string_view name, const glm::vec3& vec) const;
  void SetFloat4(std::string_view name, const glm::vec4& vec) const;
  void SetMat2(std::string_view name, const glm::mat2& mat) const;
  void SetMat3(std::string_view name, const glm::mat3& mat) const;
  void SetMat4(std::string_view name, const glm::mat4& mat) const;

  static Ref<MaterialInstance> Create(const Ref<Material>& material);

  void Bind() const;

 private:
  Ref<Material> m_Material;
};
#endif

}  // namespace Dwarfworks

#endif  // GRAPHICS_MATERIAL_H_
