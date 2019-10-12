#ifndef DWARFWORKS_H_
#define DWARFWORKS_H_

// For use by Dwarfworks applications

// -- Core -------------------------------------------------------
#include "Dwarfworks/Core/Core.h"
// ---------------------------------------------------------------

// -- Logger -----------------------------------------------------
#include "Dwarfworks/Core/Log/Log.h"
// ---------------------------------------------------------------

// -- Application ------------------------------------------------
#include "Dwarfworks/Core/Application/Application.h"
// ---------------------------------------------------------------

// -- Events -----------------------------------------------------
#include "Dwarfworks/Core/Events/EventManager.h"
// -- Core event implementations
#include "Dwarfworks/Core/Events/ApplicationEvent.h"
#include "Dwarfworks/Core/Events/KeyEvent.h"
#include "Dwarfworks/Core/Events/MouseEvent.h"
// ---------------------------------------------------------------

// -- Layers -----------------------------------------------------
#include "Dwarfworks/Core/Layers/Layer.h"
// -- DebugUI Layer implementation
#include "Dwarfworks/DebugUI/DebugUILayer.h"
// ---------------------------------------------------------------

// -- Entry point ------------------------------------------------
#include "Dwarfworks/Core/EntryPoint.h"
// ---------------------------------------------------------------

#endif  // DWARFWORKS_H_
