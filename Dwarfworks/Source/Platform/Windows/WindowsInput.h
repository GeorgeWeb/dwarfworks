#ifndef PLATFORM_WINDOWS_WINDOWS_INPUT_H_
#define PLATFORM_WINDOWS_WINDOWS_INPUT_H_

#include "Dwarfworks/Core/Input/Input.h"

namespace Dwarfworks {

class DW_API WindowsInput : public Input {
 protected:
  bool IsKeyPressedImpl(int keycode) const override;

  bool IsMouseButtonPressedImpl(int button) const override;

  std::pair<float, float> GetMousePositionImpl() const override;

  float GetMouseXImpl() const override;
  float GetMouseYImpl() const override;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_WINDOWS_WINDOWS_INPUT_H_
