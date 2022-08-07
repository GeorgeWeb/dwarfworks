#ifndef PLATFORM_LINUX_LINUX_INPUT_H_
#define PLATFORM_LINUX_LINUX_INPUT_H_

#include "Dwarfworks/Core/Input/Input.h"

namespace Dwarfworks
{
class ENGINE_API LinuxInput final : public Input
{
  public:
  protected:
    bool IsKeyPressedImpl(int keycode) const override;

    bool IsMouseButtonPressedImpl(int button) const override;

    std::pair<float, float> GetMousePositionImpl() const override;

    float GetMouseXImpl() const override;
    float GetMouseYImpl() const override;
};

} // namespace Dwarfworks

#endif // PLATFORM_LINUX_LINUX_INPUT_H_
