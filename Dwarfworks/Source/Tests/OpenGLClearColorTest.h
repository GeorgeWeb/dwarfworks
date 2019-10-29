#ifndef _TESTS_OPENGLCLEARCOLORTEST_H
#define _TESTS_OPENGLCLEARCOLORTEST_H

#include "Test.h"

namespace Tests {

class OpenGLClearColorTest final : public Test {
 public:
  OpenGLClearColorTest();

  void OnRender() override final;
  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Tests
#endif  // !_TESTS_OPENGLCLEARCOLORTEST_H
