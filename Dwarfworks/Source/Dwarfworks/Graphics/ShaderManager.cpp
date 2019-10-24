#include "dwpch.h"

#include "ShaderManager.h"

#include "Dwarfworks/Core/Log/Log.h"

#include <fstream>
namespace Dwarfworks {

ShaderManager::~ShaderManager() {
  for (auto& [key, program] : m_ShaderPrograms) {
    glDeleteProgram(program);
  }
  m_ShaderPrograms.clear();
}

void ShaderManager::CreateProgram(const std::string& programName,
                                  const std::string& vertexSourcePath,
                                  const std::string& fragmentSourcePath) {
  // Create vertex shader
  auto vertexSource = ReadShader(vertexSourcePath);

  GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexSource);

  if (!vertexShader) {
    DW_CORE_WARN("Vertex shader compilation failure for program-> {0}",
                 programName);

    DW_CORE_INFO("{0} was not created.", programName);
    return;
  }

  // Create fragment shader and check for success
  auto fragmentSource = ReadShader(fragmentSourcePath);

  GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource);
  if (!fragmentShader) {
    DW_CORE_WARN("Fragment shader compilation failure for program-> {0}",
                 programName);
    DW_CORE_INFO("{0} was not created.", programName);
    return;
  }

  // Set-up program
  auto program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link program
  glLinkProgram(program);
  int isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));

  // Check for successfull linking
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
    DW_CORE_WARN("Shader program linking failure! -> {0}", programName);
    DW_CORE_INFO("{0} was not created.", programName);

    // In this simple program, we'll just leave
    return;
  }

  m_ShaderPrograms[programName] = program;
}

void ShaderManager::BindProgram(const std::string& programName) {
  if (m_ShaderPrograms.find(programName) == m_ShaderPrograms.end()) {
    DW_CORE_ERROR("{0} does not exist in program list!", programName);
    DW_CORE_INFO("{0} was not binded.", programName);
    return;
  }
  auto rendererID = m_ShaderPrograms.at(programName);
  glUseProgram(rendererID);
  m_ActiveProgramName = programName;
}

void ShaderManager::UnbindProgram() { glUseProgram(0); }

std::string ShaderManager::GetActiveProgramName() const {
  return m_ActiveProgramName;
}

std::vector<std::string> ShaderManager::GetAllProgramNames() const {
  std::vector<std::string> allProgramNames;
  for (auto& [programName, program] : m_ShaderPrograms) {
    allProgramNames.push_back(programName);
  }
  return allProgramNames;
}

void ShaderManager::Ping() {
  DW_INFO("Shader Manager online ping.");
  DW_INFO(" Program count: {0}", m_ShaderPrograms.size());
}

GLuint ShaderManager::CreateShader(GLenum shaderType,
                                   const std::string& shaderSource) {
  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  auto source = static_cast<const char*>(shaderSource.c_str());

  // Create an shader handle
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);

  glCompileShader(shader);
  int isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

  if (!isCompiled) {
    int maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    // The maxLength includes the NULL character
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    // We don't need the shader anymore.
    glDeleteShader(shader);
    // Use the infoLog as you see fit.
    // DW_CORE_ERROR("{0}", infoLog);
    // In this simple program, we'll just leave

    return 0;
  }

  return shader;
}

std::string ShaderManager::ReadShader(const std::string& filename) {
  auto filenamePath = static_cast<const char*>(filename.c_str());
  std::string shaderCode;

  std::ifstream file;
  std::stringstream filestream;
  try {
    file.open(filenamePath);
    filestream << file.rdbuf();
    file.close();
    shaderCode = filestream.str();
  } catch (std::ifstream::failure e) {
    DW_ERROR("Can't find file path for shader {0}", filename);
    return std::string("FAILED");
  }
  return shaderCode;
}

}  // namespace Dwarfworks
