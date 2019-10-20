#include "dwpch.h"

#include "Shader.h"

#include "Dwarfworks/Core/Log/Log.h"

#include <glad/glad.h>

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

}  // namespace Dwarfworks
