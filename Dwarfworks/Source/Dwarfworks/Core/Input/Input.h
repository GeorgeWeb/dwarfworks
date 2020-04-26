#ifndef CORE_INPUT_INPUT_H_
#define CORE_INPUT_INPUT_H_

#include "Dwarfworks/Core/Core.h"

#include <atomic>
#include <mutex>

namespace Dwarfworks {

// struct DW_API InputPrefs {};

// Interface representing an Input management system
class DW_API Input {
 public:
  inline static bool IsKeyPressed(int keycode) {
    return s_Instance->IsKeyPressedImpl(keycode);
  }

  inline static bool IsMouseButtonPressed(int button) {
    return s_Instance->IsMouseButtonPressedImpl(button);
  }

  inline static std::pair<float, float> GetMousePosition() {
    return s_Instance->GetMousePositionImpl();
  }

  inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
  inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

 protected:
  virtual bool IsKeyPressedImpl(int keycode) const = 0;
  virtual bool IsMouseButtonPressedImpl(int button) const = 0;

  virtual std::pair<float, float> GetMousePositionImpl() const = 0;

  virtual float GetMouseXImpl() const = 0;
  virtual float GetMouseYImpl() const = 0;

 private:
  static Scope<Input> s_Instance;
};

}  // namespace Dwarfworks

#endif  // CORE_INPUT_INPUT_H_
