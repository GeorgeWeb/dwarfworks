// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dwarfworks {

Ref<Shader> Shader::Create(const std::string& vertexSource,
                       const std::string& fragmentSource) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      DW_CORE_ASSERT(false, "RendererAPI::None is not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
  }

  DW_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace Dwarfworks
