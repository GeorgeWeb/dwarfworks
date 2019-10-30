// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "Dwarfworks/Core/Log/Log.h"
#include "Shader.h"

namespace Dwarfworks {

Shader::Shader(const std::string& vertexSource,
               const std::string& fragmentSource) {
  // Read our shaders into the appropriate buffers
  // TODO

  // Create an empty vertex shader handle
  auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  auto source = static_cast<const char*>(vertexSource.c_str());
  glShaderSource(vertexShader, 1, &source, 0);

  // Compile the vertex shader
  glCompileShader(vertexShader);

  int isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    int maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.
    DW_CORE_ERROR("{0}", infoLog.data());
    DW_CORE_ASSERT(false, "Vertex shader compilation failure!");

    // In this simple program, we'll just leave
    return;
  }

  // Create an empty fragment shader handle
  auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Send the fragment shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = static_cast<const char*>(fragmentSource.c_str());
  glShaderSource(fragmentShader, 1, &source, 0);

  // Compile the fragment shader
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    int maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(fragmentShader);
    // Either of them. Don't leak shaders.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.
    DW_CORE_ERROR("{0}", infoLog.data());
    DW_CORE_ASSERT(false, "Fragment shader compilation failure!");

    // In this simple program, we'll just leave
    return;
  }

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  m_RendererId = glCreateProgram();
  auto program = m_RendererId;  // Temporary

  // Attach our shaders to our program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  int isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));
  if (isLinked == GL_FALSE) {
    int maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<char> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(program);
    // Don't leak shaders either.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the infoLog as you see fit.
    DW_CORE_ERROR("{0}", infoLog.data());
    DW_CORE_ASSERT(false, "Shader program linking failure!");

    // In this simple program, we'll just leave
    return;
  }

  // Always detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_RendererId); }

void Shader::Bind() const { glUseProgram(m_RendererId); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::UploadUniformBool(std::string_view name, bool val) const {
  glUniform1i(GetUniformLocation(name), static_cast<int>(val));
}

void Shader::UploadUniformInt(std::string_view name, int val) const {
  glUniform1i(GetUniformLocation(name), val);
}

void Shader::UploadUniformFloat(std::string_view name, float val) const {
  glUniform1f(GetUniformLocation(name), val);
}

void Shader::UploadUniformFloat2(std::string_view name,
                                 const glm::vec2& vec) const {
  glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::UploadUniformFloat3(std::string_view name,
                                 const glm::vec3& vec) const {
  glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::UploadUniformFloat4(std::string_view name,
                                 const glm::vec4& vec) const {
  glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::UploadUniformMat2(std::string_view name,
                               const glm::mat2& mat) const {
  glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(mat));
}

void Shader::UploadUniformMat3(std::string_view name,
                               const glm::mat3& mat) const {
  glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(mat));
}

void Shader::UploadUniformMat4(std::string_view name,
                               const glm::mat4& mat) const {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(mat));
}

int Shader::GetUniformLocation(std::string_view name) const {
  auto location = glGetUniformLocation(m_RendererId, name.data());
  if (location == -1) {
    DW_CORE_ERROR("Uniform location not found!");
  }
  return location;
}

}  // namespace Dwarfworks
