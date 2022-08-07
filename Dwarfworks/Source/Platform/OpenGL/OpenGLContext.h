#ifndef PLATFORM_OPENGL_OPENGL_CONTEXT_H
#define PLATFORM_OPENGL_OPENGL_CONTEXT_H

#include "Dwarfworks/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dwarfworks
{
static constexpr int MinimumSupportedOpenGLVersionMajor = 4;
static constexpr int MinimumSupportedOpenGLVersionMinor = 1;

class ENGINE_API OpenGLLoader;

class ENGINE_API OpenGLContext final : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow* handle);

    ~OpenGLContext() = default;

    void Initialize() const override final;
    void FlipSwapChainBuffers() const override final;

  protected:
    void MakeContextCurrent() const override final;

  private:
    Ref<OpenGLLoader> m_OpenGLLoader;
    GLFWwindow*       m_WindowHandle;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_CONTEXT_H
