// begin PCH
#include "dwpch.h"
// end PCH

#include "Material.h"

namespace Dwarfworks {

// Material

// temporary
Ref<Material> Material::Create(const Ref<Shader>& shader) {
  return CreateRef<Material>(shader);
}

void Material::Bind() const { m_Shader->Bind(); }

Material::Material(const Ref<Shader>& shader) : m_Shader(shader) {}

// Material Instance

// temporary
Ref<MaterialInstance> MaterialInstance::Create(const Ref<Material>& material) {
  return CreateRef<MaterialInstance>(material);
}

void MaterialInstance::Bind() const { m_Material->Bind(); }

MaterialInstance::MaterialInstance(const Ref<Material>& material)
    : m_Material(material) {}

void MaterialInstance::SetBool(std::string_view name, bool val) const {
  // m_Material->GetShader()->UploadUniformBool(name, val);
}

void MaterialInstance::SetInt(std::string_view name, int val) const {
  // m_Material->GetShader()->UploadUniformInt(name, val);
}

void MaterialInstance::SetFloat(std::string_view name, float val) const {
  // m_Material->GetShader()->UploadUniformFloat(name, val);
}

void MaterialInstance::SetFloat2(std::string_view name,
                                 const glm::vec2& vec) const {
  // m_Material->GetShader()->UploadUniformFloat2(name, vec);
}

void MaterialInstance::SetFloat3(std::string_view name,
                                 const glm::vec3& vec) const {
  // m_Material->GetShader()->UploadUniformFloat3(name, vec);
}

void MaterialInstance::SetFloat4(std::string_view name,
                                 const glm::vec4& vec) const {
  // m_Material->GetShader()->UploadUniformFloat4(name, vec);
}

void MaterialInstance::SetMat2(std::string_view name,
                               const glm::mat2& mat) const {
  // m_Material->GetShader()->UploadUniformMat2(name, mat);
}

void MaterialInstance::SetMat3(std::string_view name,
                               const glm::mat3& mat) const {
  // m_Material->GetShader()->UploadUniformMat3(name, mat);
}

void MaterialInstance::SetMat4(std::string_view name,
                               const glm::mat4& mat) const {
  // m_Material->GetShader()->UploadUniformMat4(name, mat);
}

}  // namespace Dwarfworks
