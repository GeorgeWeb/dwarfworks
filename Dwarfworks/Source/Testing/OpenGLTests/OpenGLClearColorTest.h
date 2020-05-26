#ifndef TESTING_OPENGL_OPENGL_CLEAR_COLOR_TEST_H_
#define TESTING_OPENGL_OPENGL_CLEAR_COLOR_TEST_H_

#include "Testing/Test.h"

namespace Testing {

class OpenGLClearColorTest final : public Test {
 public:
  OpenGLClearColorTest();

  virtual void OnRender() override final;
  virtual void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Testing

#endif  // TESTING_OPENGL_OPENGL_CLEAR_COLOR_TEST_H_
