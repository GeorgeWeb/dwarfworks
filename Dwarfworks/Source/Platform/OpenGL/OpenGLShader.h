#ifndef PLATFORM_OPENGL_OPENGL_SHADER_H_
#define PLATFORM_OPENGL_OPENGL_SHADER_H_

#include "Dwarfworks/Graphics/Shader.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

class DW_API OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& vertexSource,
               const std::string& fragmentSource);
  virtual ~OpenGLShader() override;

  // OpenGLShader(const OpenGLShader&) = default;
  // OpenGLShader& operator=(const OpenGLShader&) = default;
  // OpenGLShader(OpenGLShader&&) = default;
  // OpenGLShader& operator=(OpenGLShader&&) = default;

  virtual void Bind() const override;
  virtual void Unbind() const override;

  // void PreProcess() override {}
  // void Compile() override {}

  void UploadUniformBool(std::string_view name, bool val) const;
  void UploadUniformInt(std::string_view name, int val) const;
  void UploadUniformFloat(std::string_view name, float val) const;
  void UploadUniformFloat2(std::string_view name, const glm::vec2& vec) const;
  void UploadUniformFloat3(std::string_view name, const glm::vec3& vec) const;
  void UploadUniformFloat4(std::string_view name, const glm::vec4& vec) const;
  void UploadUniformMat2(std::string_view name, const glm::mat2& mat) const;
  void UploadUniformMat3(std::string_view name, const glm::mat3& mat) const;
  void UploadUniformMat4(std::string_view name, const glm::mat4& mat) const;

 protected:
  // virtual std::string ReadFile(const std::string& filepath) const override {}

 private:
  // TEMPORARY!
  int GetUniformLocation(std::string_view name) const;

 private:
  uint32_t m_RendererId;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_SHADER_H_
