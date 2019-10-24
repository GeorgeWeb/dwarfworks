#include "dwpch.h"

#include "TestMenu.h"

namespace Tests {
TestMenu::TestMenu(Test*& currentTestPointer)
    : m_CurrentTest(currentTestPointer) {}

void TestMenu::OnDebugUIRender() {
  for (auto& [name, instance] : m_TestList) {
    if (ImGui::Button(name.c_str())) {
      // set current test to an instance of the new test
      m_CurrentTest = instance();
    }
  }
}

}  // namespace Tests
