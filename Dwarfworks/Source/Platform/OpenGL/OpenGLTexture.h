#ifndef PLATFORM_OPENGL_OPENGL_TEXTURE_H
#define PLATFORM_OPENGL_OPENGL_TEXTURE_H

#include "Dwarfworks/Renderer/Texture.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLTexture2D final : public Texture2D
{
  public:
    explicit OpenGLTexture2D(const std::string& path);

    ~OpenGLTexture2D() override final;

    inline uint32 GetWidth() const override final { return m_Width; }
    inline uint32 GetHeight() const override final { return m_Height; }

    inline int GetFormat() const override final { return m_Format; }

    void Bind(uint32 slot = 0) const override;

  private:
    std::string m_Path;
    uint32      m_Width;
    uint32      m_Height;
    int32       m_Format;
    uint32      m_RendererId;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_TEXTURE_H
