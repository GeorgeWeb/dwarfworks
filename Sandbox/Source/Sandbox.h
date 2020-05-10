#ifndef SANDBOX_H_
#define SANDBOX_H_

// generic playground (currently 2D stuff)
#include "Playground.h"
// playground for 3D stuff
#include "Basic3D.h"

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox();
  virtual ~Sandbox() override final = default;

 private:
  std::vector<Dwarfworks::Layer*> m_Layers;
};

#endif  // SANDBOX_H_
