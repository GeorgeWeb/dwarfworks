#ifndef DWARFWORKS_PUBLIC_API_H_
#define DWARFWORKS_PUBLIC_API_H_

// For use by Dwarfworks applications

// -- Core -------------------------------------------------------
#include "Dwarfworks/Core/Core.h"
// ---------------------------------------------------------------

// -- Logger -----------------------------------------------------
#include "Dwarfworks/Core/Log/Log.h"
// ---------------------------------------------------------------

// -- Events ------------------------------------------------
#include "Dwarfworks/Events/ApplicationEvent.h"
#include "Dwarfworks/Events/KeyEvent.h"
#include "Dwarfworks/Events/MouseEvent.h"
// ...
#include "Dwarfworks/Events/EventManager.h"
// ---------------------------------------------------------------

// -- Input ------------------------------------------------------
#include "Dwarfworks/Core/Input/Input.h"
#include "Dwarfworks/Core/Input/KeyCodes.h"
#include "Dwarfworks/Core/Input/MouseButtonCodes.h"
// ---------------------------------------------------------------

// -- Timestep ---------------------------------------------------
#include "Dwarfworks/Core/Timestep.h"
// ---------------------------------------------------------------

// -- Application ------------------------------------------------
#include "Dwarfworks/Core/Application/Application.h"
// ---------------------------------------------------------------

// -- Layers -----------------------------------------------------
#include "Dwarfworks/Core/Layers/Layer.h"
#include "Dwarfworks/DebugUI/DebugUILayer.h"
// ---------------------------------------------------------------

// -- Maths ------------------------------------------------------
#include "Dwarfworks/Math/Math.h"
// ---------------------------------------------------------------

// -- Graphics ---------------------------------------------------
// ...
#include "Dwarfworks/Graphics/RenderCommand.h"
#include "Dwarfworks/Graphics/Renderer.h"
// ...
#include "Dwarfworks/Graphics/Buffer.h"
#include "Dwarfworks/Graphics/Shader.h"
#include "Dwarfworks/Graphics/VertexArray.h"
// ...
#include "Dwarfworks/Graphics/Camera.h"
#include "Dwarfworks/Graphics/CameraController.h"
// ...
#include "Dwarfworks/Graphics/Material.h"
#include "Dwarfworks/Graphics/Mesh.h"
// ---------------------------------------------------------------

// -- Factories --------------------------------------------------
#include "Dwarfworks/Factories/ShaderFactory.h"
// ---------------------------------------------------------------

// -- Entry point ------------------------------------------------
#include "Dwarfworks/Core/EntryPoint.h"
// ---------------------------------------------------------------

#endif  // DWARFWORKS_PUBLIC_API_H_
