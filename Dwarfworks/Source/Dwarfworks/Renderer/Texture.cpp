// begin PCH
#include "dwpch.h"
// end PCH

#include "Texture.h"
#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

using namespace Dwarfworks;

Ref<Texture2D> Dwarfworks::Texture2D::Create(const std::string& path)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
    }
}
