#ifndef _TESTS_OPENGLRENDERTRIANGLETEST_H
#define _TESTS_OPENGLRENDERTRIANGLETEST_H

#include "Test.h"
#include "glad/glad.h"

#include "Dwarfworks/Graphics/Shader.h"

namespace Tests {

class OpenGLRenderTriangleTest final : public Test {
 public:
  OpenGLRenderTriangleTest();

  void OnRender() override final;

 private:
  unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
  Dwarfworks::Scope<Dwarfworks::Shader> m_Shader;
};

}  // namespace Tests
#endif  // !_TESTS_OPENGLRENDERTRIANGLETEST_H
