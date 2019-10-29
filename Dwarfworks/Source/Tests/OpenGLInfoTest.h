#ifndef _TESTS_OPENGLINFOTEST_H
#define _TESTS_OPENGLINFOTEST_H

#include "Test.h"

namespace Tests {

class OpenGLInfoTest final : public Test {
 public:
  OpenGLInfoTest() = default;

  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Tests

#endif  // !_TESTS_OPENGLINFOTEST_H
