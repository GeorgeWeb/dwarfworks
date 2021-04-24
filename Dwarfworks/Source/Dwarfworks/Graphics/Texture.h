#ifndef GRAPHICS_TEXTURE_H_
#define GRAPHICS_TEXTURE_H_

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks
{
class ENGINE_API Texture
{
  public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const  = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual int GetFormat() const = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;
};

class ENGINE_API Texture2D : public Texture
{
  public:
    static Ref<Texture2D> Create(const std::string& path);
};

} // namespace Dwarfworks

#endif // GRAPHICS_TEXTURE_H_
