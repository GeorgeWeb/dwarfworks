#ifndef PLATFORM_OPENGL_OPENGL_SHADER_H_
#define PLATFORM_OPENGL_OPENGL_SHADER_H_

#include "Dwarfworks/Graphics/Shader.h"

namespace Dwarfworks {

class DW_API OpenGLShader : public Shader {
 public:
  explicit OpenGLShader(std::string_view filepath);
  OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource);
  virtual ~OpenGLShader() override;

  virtual void Bind() const override;
  virtual void Unbind() const override;

  // void PreProcess() override {}
  // void Compile() override {}

  virtual void SetInt(std::string_view name, int value) const override;
  virtual void SetIntArray(std::string_view name, int* values, uint32_t count) const override;
  virtual void SetFloat(std::string_view name, float value) const override;
  virtual void SetFloatArray(std::string_view name, float* values, uint32_t count) const override;
  virtual void SetFloat2(std::string_view name, const glm::vec2& value) const override;
  virtual void SetFloat3(std::string_view name, const glm::vec3& value) const override;
  virtual void SetFloat4(std::string_view name, const glm::vec4& value) const override;
  virtual void SetMat2(std::string_view name, const glm::mat2& value) const override;
  virtual void SetMat3(std::string_view name, const glm::mat3& value) const override;
  virtual void SetMat4(std::string_view name, const glm::mat4& value) const override;

  virtual const std::string& GetName() const override { return m_Name; }

  void UploadUniformBool(std::string_view name, bool value) const;
  void UploadUniformInt(std::string_view name, int value) const;
  void UploadUniformIntArray(std::string_view name, int* values, uint32_t count) const;
  void UploadUniformFloat(std::string_view name, float val) const;
  void UploadUniformFloatArray(std::string_view name, float* values, uint32_t count) const;
  void UploadUniformFloat2(std::string_view name, const glm::vec2& value) const;
  void UploadUniformFloat3(std::string_view name, const glm::vec3& value) const;
  void UploadUniformFloat4(std::string_view name, const glm::vec4& value) const;
  void UploadUniformMat2(std::string_view name, const glm::mat2& value) const;
  void UploadUniformMat3(std::string_view name, const glm::mat3& value) const;
  void UploadUniformMat4(std::string_view name, const glm::mat4& value) const;

  // void UploadUniformBuffer() const;

 private:
  uint32_t m_RendererId;
  std::string m_Name;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_SHADER_H_
