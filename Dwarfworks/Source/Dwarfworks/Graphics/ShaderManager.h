#ifndef _GRAPHICS_SHADER_MANAGER_H
#define _GRAPHICS_SHADER_MANAGER_H

#include "Dwarfworks/Core/Core.h"

#include <glad/glad.h>

#include <map>
#include <string>
#include <vector>

namespace Dwarfworks {
class DW_API ShaderManager {
 public:
  ShaderManager() {}
  ~ShaderManager();

  // Singleton access
  static ShaderManager& GetInstance() {
    static ShaderManager instance;  // Guaranteed to be destroyed.
                                    // Instantiated on first use.
    return instance;
  }

  // Remove constructor and assignments
  ShaderManager(ShaderManager const&) = delete;
  void operator=(ShaderManager const&) = delete;

  // Program operations
  void CreateProgram(const std::string& programName,
                     const std::string& vertexSourcePath,
                     const std::string& fragmentSourcePath);

  void BindProgram(const std::string& programName);
  void UnbindProgram();

  // For use in Debug UI (TODO: should only be defined at debug mode)
  std::string GetActiveProgramName() const;
  std::vector<std::string> GetAllProgramNames() const;

  void InfoPing();

 private:
  // Creates a shader program
  GLuint CreateShader(GLenum shaderType, const std::string& source);
  std::string ReadShader(const std::string& filename);
  // Container for all shader programs
  std::map<std::string, GLuint> m_ShaderPrograms;
  // For use in Debug UI (TODO: should only be defined at debug mode)
  std::string m_ActiveProgramName;
};

}  // namespace Dwarfworks
#endif  // _GRAPHICS_SHADER_MANAGER_H
