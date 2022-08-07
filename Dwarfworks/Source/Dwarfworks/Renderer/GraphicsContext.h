#ifndef GRAPHICS_GRAPHICS_CONTEXT_H
#define GRAPHICS_GRAPHICS_CONTEXT_H

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks
{
class ENGINE_API GraphicsContext
{
  public:
    virtual ~GraphicsContext() = default;

    virtual void Initialize() const  = 0;
    virtual void FlipSwapChainBuffers() const = 0;

    static GraphicsContext* Create(void* window);

  protected:
    virtual void MakeContextCurrent() const = 0;
};

} // namespace Dwarfworks

#endif // GRAPHICS_GRAPHICS_CONTEXT_H
