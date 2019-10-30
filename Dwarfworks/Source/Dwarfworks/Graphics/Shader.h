#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

class DW_API Shader {
 public:
  Shader(const std::string& vertexSource, const std::string& fragmentSource);
  ~Shader();

  Shader(const Shader&);
  Shader& operator=(const Shader&);
  Shader(Shader&&);
  Shader& operator=(Shader&&);

  void Bind() const;
  void Unbind() const;

  void PreProcess() {}
  void Compile() {}
  void Link() {}

  void UploadUniformBool(std::string_view name, bool val) const;
  void UploadUniformInt(std::string_view name, int val) const;
  void UploadUniformFloat(std::string_view name, float val) const;
  void UploadUniformFloat2(std::string_view name, const glm::vec2& vec) const;
  void UploadUniformFloat3(std::string_view name, const glm::vec3& vec) const;
  void UploadUniformFloat4(std::string_view name, const glm::vec4& vec) const;
  void UploadUniformMat2(std::string_view name, const glm::mat2& mat) const;
  void UploadUniformMat3(std::string_view name, const glm::mat3& mat) const;
  void UploadUniformMat4(std::string_view name, const glm::mat4& mat) const;

 private:
  // TEMPORARY!
  int GetUniformLocation(std::string_view name) const;

 private:
  std::string ReadFile(const std::string& filepath) {}

 private:
  uint32_t m_RendererId;
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_SHADER_H_
