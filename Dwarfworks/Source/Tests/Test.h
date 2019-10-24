#ifndef TEST_H_
#define TEST_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Layers/Layer.h"

#include "imgui.h"

namespace Tests {

class Test : public Dwarfworks::Layer {
 public:
  Test() : Layer("TestLayer") {}
  virtual ~Test() = default;

  // virtual void OnEvent(Dwarfworks::Event& event) override {}
  virtual void OnUpdate() override {}
  virtual void OnRender() override {}  // TODO: Integrate with Renderer
  virtual void OnDebugUIRender() override {}
};

}  // namespace Tests

#endif  // TEST_H_
