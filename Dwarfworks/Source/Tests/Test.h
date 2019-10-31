#ifndef TEST_H_
#define TEST_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Layers/Layer.h"
#include "imgui.h"

namespace Tests {

class Test : public Dwarfworks::Layer {
 public:
  Test() : Layer() {}
  // Test(const std::string& name) : Layer(name) {}

  virtual ~Test() = default;

  virtual void OnRender() override {}
  virtual void OnDebugUIRender() override {}
};

}  // namespace Tests

#endif  // TEST_H_
