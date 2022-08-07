#pragma once

#include "Dwarfworks/Core/Core.h"

// Getting the Device should be done through the Adapter
// All the RHI commands should be accessible from the Adapter

namespace Dwarfworks
{
/**
 * @brief
 *
 */
class ENGINE_API Adapter
{
  public:
    Adapter() = default;

    static Scope<Adapter> Create();

  private:
};
} // namespace Dwarfworks
