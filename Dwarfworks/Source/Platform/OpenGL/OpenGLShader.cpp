// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Core/Log/Log.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>

namespace Dwarfworks {

static GLenum ShaderTypeFromString(const std::string& type) {
  if (type == "vertex") {
    return GL_VERTEX_SHADER;
  }
  if (type == "fragment" || type == "pixel") {
    return GL_FRAGMENT_SHADER;
  }
  DW_CORE_ASSERT(false, "Unknown shader type!");
  return 0;
}

OpenGLShader::OpenGLShader(const std::string& filepath) {
  std::string source = ReadFile(filepath);
  auto shaderSources = PreProcess(source);
  Compile(shaderSources);
  
  // Extract name from filepath
  auto lastSlash = filepath.find_last_of("/\\");
  lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
  auto lastDot = filepath.rfind('.');
  auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
  m_Name = filepath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string& name,
						   const std::string& vertexSource, const std::string& fragmentSource) {
  std::unordered_map<GLenum, std::string> shaderSources;
  shaderSources[GL_VERTEX_SHADER] = vertexSource;
  shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
  Compile(shaderSources);
}

OpenGLShader::~OpenGLShader() { 
  glDeleteProgram(m_RendererId);
}

std::string OpenGLShader::ReadFile(const std::string& filepath) {
  std::string result;
  std::ifstream in(filepath, std::ios::in | std::ios::binary);
  if (in) {
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	if (size != -1) {
	  result.resize(size);
	  in.seekg(0, std::ios::beg);
	  in.read(&result[0], size);
	  in.close();
	} else {
	  DW_CORE_ERROR("Could not read from file '{0}'", filepath);
    }
  } else {
    DW_CORE_ERROR("Could not open file '{0}'", filepath);
  }

	return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
  std::unordered_map<GLenum, std::string> shaderSources;

  const char* typeToken = "#type";
  size_t typeTokenLength = strlen(typeToken);
  // Start of shader type declaration line
  size_t pos = source.find(typeToken, 0);
  while (pos != std::string::npos) {
    // End of shader type declaration line
    size_t eol = source.find_first_of("\r\n", pos);
    DW_CORE_ASSERT(eol != std::string::npos, "Syntax error");
	
    // Start of shader type name (after "#type " keyword)
    size_t begin = pos + typeTokenLength + 1;
    std::string type = source.substr(begin, eol - begin);
    DW_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
	
    // Start of shader code after shader type declaration line
    size_t nextLinePos = source.find_first_not_of("\r\n", eol);
    DW_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
	
    // Start of next shader type declaration line
    pos = source.find(typeToken, nextLinePos); 
    shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
  }
  return shaderSources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
  GLuint program = glCreateProgram();
  DW_CORE_ASSERT(shaderSources.size() <= 2, "Only 2 shaders are supported for now!");
  std::array<GLenum, 2> glShaderIDs;
  int glShaderIDIndex = 0;
  for (const auto& [type, source] : shaderSources) {
    GLuint shader = glCreateShader(type);
	
    const GLchar* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, 0);
	
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

      glDeleteShader(shader);

      DW_CORE_ERROR("{0}", infoLog.data());
      DW_CORE_ASSERT(false, "Shader compilation failure!");
      break;
    }

    glAttachShader(program, shader);
    glShaderIDs[glShaderIDIndex++] = shader;
  }

  m_RendererId = program;

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));
  if (GL_FALSE == isLinked) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(program);
	// and the shader objects
	std::for_each(glShaderIDs.begin(), glShaderIDs.end(), glDeleteShader);

    DW_CORE_ERROR("{0}", infoLog.data());
    DW_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  // Detach from program and delete shaders
  for (auto id : glShaderIDs) {
    glDetachShader(program, id);
	glDeleteShader(id);
  }
}

void OpenGLShader::Bind() const { glUseProgram(m_RendererId); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::SetInt(const std::string& name, int value) const {
  UploadUniformInt(name, value);
}

void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count) const {
  UploadUniformIntArray(name, values, count);
}

void OpenGLShader::SetFloat(const std::string& name, float value) const {
  UploadUniformFloat(name, value);
}

void OpenGLShader::SetFloatArray(const std::string& name, float* values, uint32_t count) const {
	UploadUniformFloatArray(name, values, count);
}

void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value) const {
  UploadUniformFloat2(name, value);
}

void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) const {
  UploadUniformFloat3(name, value);
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) const {
  UploadUniformFloat4(name, value);
}

void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& value) const {
  UploadUniformMat2(name, value);
}

void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value) const {
  UploadUniformMat3(name, value);
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) const {
  UploadUniformMat4(name, value);
}

void OpenGLShader::UploadUniformBool(const std::string& name, bool value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform1i(location, static_cast<int>(value));
}

void OpenGLShader::UploadUniformInt(const std::string& name, int value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform1i(location, value);
}

void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform1iv(location, count, values);
}

void OpenGLShader::UploadUniformFloat(const std::string& name, float val) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform1f(location, val);
}

void OpenGLShader::UploadUniformFloatArray(const std::string& name, float* values, uint32_t count) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform1fv(location, count, values);
}

void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat2(const std::string& name, const glm::mat2& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value) const {
  GLint location = glGetUniformLocation(m_RendererId, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}  // namespace Dwarfworks
