#pragma once

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks
{
/**
 * @brief
 *
 */
class ENGINE_API OpenGLLoader
{
  public:
    virtual ~OpenGLLoader() = default;

    virtual bool LoadOpenGLFunctions() = 0;
};

/**
 * @brief
 *
 */
class ENGINE_API GLADOpenGLLoader final : public OpenGLLoader
{
    typedef void* (*LoadProcess)(const char* name);

  public:
    GLADOpenGLLoader();

    ~GLADOpenGLLoader();

    bool LoadOpenGLFunctions() override final;

  private:
    LoadProcess m_LoadProcess;
};
} // namespace Dwarfworks
