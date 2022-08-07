#ifndef PLATFORM_MAC_MAC_INPUT_H
#define PLATFORM_MAC_MAC_INPUT_H

#include "Dwarfworks/Core/Input/Input.h"

namespace Dwarfworks
{
class ENGINE_API MacInput final : public Input
{
  public:
    virtual ~MacInput() = default;

  protected:
    virtual bool IsKeyPressedImpl(int keycode) const override;

    virtual bool IsMouseButtonPressedImpl(int button) const override;

    virtual std::pair<float, float> GetMousePositionImpl() const override;

    virtual float GetMouseXImpl() const override;
    virtual float GetMouseYImpl() const override;
};

} // namespace Dwarfworks

#endif // PLATFORM_MAC_MAC_INPUT_H
