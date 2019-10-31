#ifndef _TESTS_OPENGLCLEARCOLORTEST_H
#define _TESTS_OPENGLCLEARCOLORTEST_H

#include "Testing/Test.h"

namespace Testing {

class OpenGLClearColorTest final : public Test {
 public:
  OpenGLClearColorTest();

  void OnRender() override final;
  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Testing
#endif  // !_TESTS_OPENGLCLEARCOLORTEST_H
