#ifndef TESTING_OPENGL_OPENGLRENDERTRIANGLETEST_H
#define TESTING_OPENGL_OPENGLRENDERTRIANGLETEST_H

#include "Dwarfworks/Graphics/Shader.h"
#include "Testing/Test.h"

namespace Testing {

class OpenGLRenderTriangleTest final : public Test {
 public:
  OpenGLRenderTriangleTest();

  virtual void OnRender() override final;

 private:
  unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
  Dwarfworks::Scope<Dwarfworks::Shader> m_Shader;
};

}  // namespace Testing
#endif  // !_TESTS_OPENGLRENDERTRIANGLETEST_H
