#ifndef PLATFORM_OPENGL_OPENGL_CONTEXT_H_
#define PLATFORM_OPENGL_OPENGL_CONTEXT_H_

#include "Dwarfworks/Graphics/GraphicsContext.h"

// forward decl.
struct GLFWwindow;

namespace Dwarfworks {

class DW_API OpenGLContext : public GraphicsContext {
 public:
  OpenGLContext(GLFWwindow* windowHandle);

  void Initialize() override;
  void SwapBuffers() override;

 private:
  GLFWwindow* m_WindowHandle;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_CONTEXT_H_
