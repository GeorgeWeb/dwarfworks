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

  static Ref<Shader> Create(const std::string& vertexSource,
                            const std::string& fragmentSource);

 protected:
  // virtual std::string ReadFile(const std::string& filepath) const {}
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_SHADER_H_
