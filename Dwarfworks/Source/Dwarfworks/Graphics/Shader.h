#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

class DW_API Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  // virtual void PreProcess() = 0;
  // virtual void Compile() = 0;

  virtual void SetInt(std::string_view name, int value) const = 0;
  virtual void SetIntArray(std::string_view name, int* values, uint32_t count) const = 0;
  virtual void SetFloat(std::string_view name, float value) const = 0;
  virtual void SetFloatArray(std::string_view name, float* values, uint32_t count) const = 0;
  virtual void SetFloat2(std::string_view name, const glm::vec2& value) const = 0;
  virtual void SetFloat3(std::string_view name, const glm::vec3& value) const = 0;
  virtual void SetFloat4(std::string_view name, const glm::vec4& value) const = 0;
  virtual void SetMat2(std::string_view name, const glm::mat2& value) const = 0;
  virtual void SetMat3(std::string_view name, const glm::mat3& value) const = 0;
  virtual void SetMat4(std::string_view name, const glm::mat4& value) const = 0;

  virtual const std::string& GetName() const = 0;

  static Ref<Shader> Create(std::string_view filepath);
  static Ref<Shader> Create(std::string_view vertexSource, std::string_view fragmentSource);

 private:
  inline std::string ReadFile(std::string_view filePath) const {
	// TODO: Implement!
	return {0};
  }
};

class ShaderLibrary
{
public:
	void Add(const std::string& name, const Ref<Shader>& shader);
	void Add(const Ref<Shader>& shader);
	Ref<Shader> Load(const std::string& filepath);
	Ref<Shader> Load(const std::string& name, const std::string& filepath);

	Ref<Shader> Get(const std::string& name);

	bool Exists(const std::string& name) const;
private:
	std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};


}  // namespace Dwarfworks

#endif  // GRAPHICS_SHADER_H_
