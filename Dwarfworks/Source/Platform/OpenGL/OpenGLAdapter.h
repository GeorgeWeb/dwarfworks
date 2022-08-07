#pragma once

#include "Dwarfworks/Renderer/Adapter.h"

#include "OpenGLDriver.h"

namespace Dwarfworks
{
/**
 * @brief
 *
 */
class ENGINE_API OpenGLAdapter final : public Adapter
{
  public:
    OpenGLAdapter();

    ~OpenGLAdapter() = default;

  private:
    Scope<OpenGL::Driver> m_OpenGLDriver;
};

} // namespace Dwarfworks
