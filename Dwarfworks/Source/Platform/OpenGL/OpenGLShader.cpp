// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Core/Log/Log.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Dwarfworks {

OpenGLShader::OpenGLShader(std::string_view filepath) {
	// TODO: Implement!
}

OpenGLShader::OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource) {
  // TODO: Read our shaders into the appropriate buffers
  const char* source = {0};

  // Create an empty vertex shader handle
  auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = vertexSource.data();
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
  source = fragmentSource.data();
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
    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

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

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_RendererId); }

void OpenGLShader::Bind() const { glUseProgram(m_RendererId); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::SetInt(std::string_view name, int value) const {
  UploadUniformInt(name, value);
}

void OpenGLShader::SetIntArray(std::string_view name, int* values, uint32_t count) const {
  UploadUniformIntArray(name, values, count);
}

void OpenGLShader::SetFloat(std::string_view name, float value) const {
  UploadUniformFloat(name, value);
}

void OpenGLShader::SetFloatArray(std::string_view name, float* values, uint32_t count) const {
	UploadUniformFloatArray(name, values, count);
}

void OpenGLShader::SetFloat2(std::string_view name, const glm::vec2& value) const {
  UploadUniformFloat2(name, value);
}

void OpenGLShader::SetFloat3(std::string_view name, const glm::vec3& value) const {
  UploadUniformFloat3(name, value);
}

void OpenGLShader::SetFloat4(std::string_view name, const glm::vec4& value) const {
  UploadUniformFloat4(name, value);
}

void OpenGLShader::SetMat2(std::string_view name, const glm::mat2& value) const {
  UploadUniformMat2(name, value);
}

void OpenGLShader::SetMat3(std::string_view name, const glm::mat3& value) const {
  UploadUniformMat3(name, value);
}

void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& value) const {
  UploadUniformMat4(name, value);
}

void OpenGLShader::UploadUniformBool(std::string_view name, bool value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform1i(location, static_cast<int>(value));
}

void OpenGLShader::UploadUniformInt(std::string_view name, int value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform1i(location, value);
}

void OpenGLShader::UploadUniformIntArray(std::string_view name, int* values, uint32_t count) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform1iv(location, count, values);
}

void OpenGLShader::UploadUniformFloat(std::string_view name, float val) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform1f(location, val);
}

void OpenGLShader::UploadUniformFloatArray(std::string_view name, float* values, uint32_t count) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform1fv(location, count, values);
}

void OpenGLShader::UploadUniformFloat2(std::string_view name, const glm::vec2& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(std::string_view name, const glm::vec3& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(std::string_view name, const glm::vec4& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat2(std::string_view name, const glm::mat2& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::UploadUniformMat3(std::string_view name, const glm::mat3& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::UploadUniformMat4(std::string_view name, const glm::mat4& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.data());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}  // namespace Dwarfworks
