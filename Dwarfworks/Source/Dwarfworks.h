#ifndef DWARFWORKS_PUBLIC_API_H
#define DWARFWORKS_PUBLIC_API_H

// For use by Dwarfworks applications

// -- Core -------------------------------------------------------
#include "Dwarfworks/Core/Core.h"
// ---------------------------------------------------------------

// -- Logger -----------------------------------------------------
#include "Dwarfworks/Core/Log/Log.h"
// ---------------------------------------------------------------

// -- Events ------------------------------------------------
#include "Dwarfworks/Event/ApplicationEvent.h"
#include "Dwarfworks/Event/KeyEvent.h"
#include "Dwarfworks/Event/MouseEvent.h"
#include "Dwarfworks/Event/EventDispatcher.h"
// ---------------------------------------------------------------

// -- Input ------------------------------------------------------
#include "Dwarfworks/Core/Input/Input.h"
#include "Dwarfworks/Core/Input/KeyCodeDefinitions.h"
#include "Dwarfworks/Core/Input/MouseButtonDefinitions.h"
// ---------------------------------------------------------------

// -- Timestep ---------------------------------------------------
#include "Dwarfworks/Core/Timestep.h"
// ---------------------------------------------------------------

// -- Application ------------------------------------------------
#include "Dwarfworks/Core/Application/Application.h"
// ---------------------------------------------------------------

// -- Layer ------------------------------------------------------
#include "Dwarfworks/Core/Layer/Layer.h"
// ---------------------------------------------------------------

// -- ImGui ------------------------------------------------------
#include "Dwarfworks/DebugUI/DebugUILayer.h"
// ---------------------------------------------------------------

// -- Math -------------------------------------------------------
#include "Dwarfworks/Math/Math.h"
// ---------------------------------------------------------------

// -- Renderer ---------------------------------------------------
#include "Dwarfworks/Renderer/RenderCommand.h"
#include "Dwarfworks/Renderer/Renderer.h"
#include "Dwarfworks/Renderer/2D/Renderer2D.h"
#include "Dwarfworks/Renderer/Buffer.h"
#include "Dwarfworks/Renderer/Shader.h"
#include "Dwarfworks/Renderer/Texture.h"
#include "Dwarfworks/Renderer/VertexArray.h"
#include "Dwarfworks/Renderer/Camera.h"
#include "Dwarfworks/Renderer/CameraController.h"
// ---------------------------------------------------------------

#endif // DWARFWORKS_PUBLIC_API_H
