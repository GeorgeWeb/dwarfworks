#ifndef TEST_H_
#define TEST_H_

#include "dwpch.h"

namespace Tests {

class Test {
 public:
  Test() = default;
  virtual ~Test() = default;

  // There is no Timesetup support in Dwarfworks yet
  virtual void OnUpdate(float deltaTime = 0.0f) {}
  virtual void OnRender() {}
  virtual void OnDebugRender() {}
};

class TestMenu : public Test {
  using createTestFunc_t = std::function<Test*()>;

 public:
  explicit TestMenu(Test*& currentTestPointer);

  void OnDebugRender() override;

 private:
  // reference to test pointer that allows mutation/change
  Test*& m_CurrentTest;

  // Test instance sort of structure in a contiguous collection
  std::vector<std::pair<std::string, createTestFunc_t>> m_TestList;
};

}  // namespace Tests

#endif  // TEST_H_
