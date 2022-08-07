#pragma once

#include "SandboxLayer.h"

class Sandbox final : public Dwarfworks::Application
{
  public:
    Sandbox();
    ~Sandbox();

    void OnEvent(Dwarfworks::Event &event) override final;
};
