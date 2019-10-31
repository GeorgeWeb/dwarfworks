#ifndef TESTING_OPENGL_OPENGL_INFO_TEST_H_
#define TESTING_OPENGL_OPENGL_INFO_TEST_H_

#include "Testing/Test.h"

namespace Testing {

class OpenGLInfoTest final : public Test {
 public:
  OpenGLInfoTest() = default;

  virtual void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Testing

#endif  // TESTING_OPENGL_OPENGL_INFO_TEST_H_
