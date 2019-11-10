#ifndef SANDBOX_H_
#define SANDBOX_H_

#include "Playground.h"

class Sandbox : public Dwarfworks::Application {
 public:
  Sandbox();
  virtual ~Sandbox() override;

 private:
  Dwarfworks::Layer* m_Playground;
};

#endif  // SANDBOX_H_
