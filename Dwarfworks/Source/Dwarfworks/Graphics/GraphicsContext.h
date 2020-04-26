#ifndef GRAPHICS_GRAPHICS_CONTEXT_H_
#define GRAPHICS_GRAPHICS_CONTEXT_H_

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks {

class DW_API GraphicsContext {
 public:
  virtual ~GraphicsContext() = default;

  virtual void Initialize() = 0;
  virtual void SwapBuffers() = 0;

  static Scope<GraphicsContext> Create(void* window);
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_GRAPHICS_CONTEXT_H_
