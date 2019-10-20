#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include "Dwarfworks/Core/Core.h"

#include <string>

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

 private:
  std::string ReadFile(const std::string& filepath) {}

 private:
  uint32_t m_RendererId;
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_SHADER_H_
