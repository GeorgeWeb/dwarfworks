// begin PCH
#include "dwpch.h"
// end PCH

#include "Texture.h"
#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Dwarfworks
{
Ref<Texture2D> Dwarfworks::Texture2D::Create(const std::string& path)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None: DW_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
    }

    DW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Dwarfworks
