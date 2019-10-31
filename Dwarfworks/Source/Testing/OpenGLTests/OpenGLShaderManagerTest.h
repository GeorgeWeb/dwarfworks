#ifndef TESTING_OPENGL_OPENGL_SHADER_MANAGER_TEST_H_
#define TESTING_OPENGL_OPENGL_SHADER_MANAGER_TEST_H_

#include "Dwarfworks/Graphics/ShaderManager.h"
#include "Testing/Test.h"

namespace Testing {

class OpenGLShaderManagerTest final : public Test {
 public:
  OpenGLShaderManagerTest();

  virtual void OnRender() override final;
  virtual void OnDebugUIRender() override final;

 private:
  unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
  std::string m_Program1 = "Normal Shader Program";
  std::string m_Program2 = "Dark Multicolor Program";
  Dwarfworks::ShaderManager& m_ShaderManager;
};

}  // namespace Testing

#endif  // TESTING_OPENGL_OPENGL_SHADER_MANAGER_TEST_H_
