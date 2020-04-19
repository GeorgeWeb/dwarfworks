#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks {

class DW_API Shader {
 public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  // virtual void PreProcess() = 0;
  // virtual void Compile() = 0;

  // virtual void UploadUniformBuffer() = 0;

  // From source
  static Ref<Shader> Create(std::string_view vertexSource, std::string_view fragmentSource);
  static Ref<Shader> Create(std::string_view source);

  // From File
  // TODO

 private:
  inline const char* const ReadFile(std::string_view filePath) const {
	return {0};
  }
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_SHADER_H_
