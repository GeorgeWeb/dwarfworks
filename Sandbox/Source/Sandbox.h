#ifndef SANDBOX_H_
#define SANDBOX_H_

// Engine and common defines
#include "Common.h"

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox();
  virtual ~Sandbox() override final = default;
};

#endif  // SANDBOX_H_
