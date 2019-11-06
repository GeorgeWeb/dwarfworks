#ifndef SANDBOX_H_
#define SANDBOX_H_

#include "Playground.h"

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox();
  virtual ~Sandbox() override;

 private:
  Dwarfworks::Layer* m_Playground;
};

#endif // SANDBOX_H_
