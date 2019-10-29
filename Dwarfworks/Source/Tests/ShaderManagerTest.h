#ifndef SHADER_MANAGER_TEST_
#define SHADER_MANAGER_TEST_

#include "Dwarfworks/Graphics/ShaderManager.h"
#include "Test.h"

namespace Tests {

class ShaderManagerTest final : public Test {
 public:
  ShaderManagerTest();

  void OnRender() override final;
  void OnDebugUIRender() override final;

 private:
  unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
  std::string m_Program1 = "Normal Shader Program";
  std::string m_Program2 = "Dark Multicolor Program";
  Dwarfworks::ShaderManager& m_ShaderManager;
};

}  // namespace Tests

#endif  // SHADER_MANAGER_TEST_
