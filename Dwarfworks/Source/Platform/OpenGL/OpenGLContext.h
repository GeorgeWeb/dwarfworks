#ifndef PLATFORM_OPENGL_OPENGL_CONTEXT_H_
#define PLATFORM_OPENGL_OPENGL_CONTEXT_H_

#include "Dwarfworks/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Dwarfworks
{
static constexpr int MinimumSupportedOpenGLVersionMajor = 4;
static constexpr int MinimumSupportedOpenGLVersionMinor = 3;

class ENGINE_API OpenGLContext : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow* handle);
    virtual ~OpenGLContext() override = default;

    virtual void Initialize() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_CONTEXT_H_
