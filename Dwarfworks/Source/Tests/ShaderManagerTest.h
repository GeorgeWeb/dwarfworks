#ifndef _TESTS_SHADER_MANAGER_TEST
#define _TESTS_SHADER_MANAGER_TEST

#include "Test.h"

#include "Dwarfworks/Graphics/ShaderManager.h"

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
  // Dwarfworks::ShaderManager SM;
};

}  // namespace Tests

#endif  // _TESTS_SHADER_MANAGER_TEST
