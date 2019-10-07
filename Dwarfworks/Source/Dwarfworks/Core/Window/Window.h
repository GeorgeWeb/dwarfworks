#ifndef CORE_WINDOW_WINDOW_H_
#define CORE_WINDOW_WINDOW_H_

#include "dwpch.h"

#include "../Core.h"
#include "../Events/EventManager.h"

namespace Dwarfworks {

/// <summary>	An api. </summary>
///
/// <remarks>	Georg, 07/10/2019. </remarks>

struct DW_API WindowProps {
  std::string Title;
  unsigned int Width;
  unsigned int Height;

  /// <summary>	Constructor. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <param name="title"> 	(Optional) The title. </param>
  /// <param name="width"> 	(Optional) The width. </param>
  /// <param name="height">	(Optional) The height. </param>

  explicit WindowProps(const std::string& title = "Dwarfworks Engine",
                       unsigned int width = 1280, unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

//
// Implemented per platform

/// <summary>	Interface representing a desktop system based window.
/// Implemented per platform </summary>
///
/// <remarks>	Georg, 07/10/2019. </remarks>

class DW_API Window {
 public:
  /// <summary>	The event callback function. </summary>
  using EventCallbackFn = std::function<void(Event&)>;

  // CRTP or no CRTP, we need the virtual destructor

  /// <summary>	Destructor. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>

  virtual ~Window() = default;

  /// <summary>	Executes the update action. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>

  virtual void OnUpdate() = 0;

  /// <summary>	Gets the width. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <returns>	The width. </returns>

  virtual unsigned int GetWidth() const = 0;

  /// <summary>	Gets the height. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <returns>	The height. </returns>

  virtual unsigned int GetHeight() const = 0;

  // Window attributes

  /// <summary>	Callback, called when the set event. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <param name="callback">	The callback. </param>

  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

  /// <summary>	Sets v synchronise. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <param name="isEnabled">	True if is enabled, false if not. </param>

  virtual void SetVSync(bool isEnabled) = 0;

  /// <summary>	Query if this object is v synchronise. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <returns>	True if v synchronise, false if not. </returns>

  virtual bool IsVSync() const = 0;

  // Here just for a remainder for future implementation
  // virtual void* GetNativeWindow() const = 0;

  /// <summary>	Creates a new Window*. </summary>
  ///
  /// <remarks>	Georg, 07/10/2019. </remarks>
  ///
  /// <param name="props">	(Optional) The properties. </param>
  ///
  /// <returns>	Null if it fails, else a pointer to a Window. </returns>

  static Window* Create(const WindowProps& props = WindowProps{});
};

}  // namespace Dwarfworks

#endif  // CORE_WINDOW_WINDOW_H_
