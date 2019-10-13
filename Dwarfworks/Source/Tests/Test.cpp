#include "dwpch.h"

#include "Test.h"

#include "Dwarfworks/DebugUI/DebugUILayer.h"

namespace Tests {

TestMenu::TestMenu(Test*& currentTestPointer)
    : m_CurrentTest(currentTestPointer) {}

void TestMenu::OnDebugRender() {
  for (auto& test : m_TestList) {
    // TODO
  }
}

}  // namespace Tests
