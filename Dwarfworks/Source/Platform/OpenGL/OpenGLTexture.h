#ifndef PLATFORM_OPENGL_OPENGL_TEXTURE_H_
#define PLATFORM_OPENGL_OPENGL_TEXTURE_H_

#include "Dwarfworks/Graphics/Texture.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLTexture2D : public Texture2D
{
  public:
    explicit OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D() override;

    virtual uint32_t GetWidth() const override { return m_Width; }
    virtual uint32_t GetHeight() const override { return m_Height; }

    virtual int GetFormat() const override { return m_Format; }

    virtual void Bind(uint32_t slot = 0) const override;

  private:
    std::string m_Path;
    uint32_t    m_Width, m_Height;
    int         m_Format;
    uint32_t    m_RendererId;
};

} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_TEXTURE_H_
