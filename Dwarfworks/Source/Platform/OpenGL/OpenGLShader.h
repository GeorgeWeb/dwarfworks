#ifndef PLATFORM_OPENGL_OPENGL_SHADER_H_
#define PLATFORM_OPENGL_OPENGL_SHADER_H_

#include "Dwarfworks/Graphics/Shader.h"
#include "Dwarfworks/Math/Math.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Dwarfworks {

class DW_API OpenGLShader : public Shader {
 public:
  explicit OpenGLShader(const std::string& filepath);
  OpenGLShader(const std::string& name,
	           const std::string& vertexSource, const std::string& fragmentSource);
  virtual ~OpenGLShader() override;

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void SetInt(const std::string& name, int value) const override;
  virtual void SetIntArray(const std::string& name, int* values, uint32_t count) const override;
  virtual void SetFloat(const std::string& name, float value) const override;
  virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) const override;
  virtual void SetFloat2(const std::string& name, const glm::vec2& value) const override;
  virtual void SetFloat3(const std::string& name, const glm::vec3& value) const override;
  virtual void SetFloat4(const std::string& name, const glm::vec4& value) const override;
  virtual void SetMat2(const std::string& name, const glm::mat2& value) const override;
  virtual void SetMat3(const std::string& name, const glm::mat3& value) const override;
  virtual void SetMat4(const std::string& name, const glm::mat4& value) const override;

  virtual const std::string& GetName() const override { return m_Name; }

  void UploadUniformBool(const std::string& name, bool value) const;
  void UploadUniformInt(const std::string& name, int value) const;
  void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;
  void UploadUniformFloat(const std::string& name, float val) const;
  void UploadUniformFloatArray(const std::string& name, float* values, uint32_t count) const;
  void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
  void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
  void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;
  void UploadUniformMat2(const std::string& name, const glm::mat2& value) const;
  void UploadUniformMat3(const std::string& name, const glm::mat3& value) const;
  void UploadUniformMat4(const std::string& name, const glm::mat4& value) const;

  // void UploadUniformBuffer() const;

 private:
  std::string ReadFile(const std::string& filepath);
  std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
  void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

 private:
  uint32_t m_RendererId;
  std::string m_Name;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_SHADER_H_
