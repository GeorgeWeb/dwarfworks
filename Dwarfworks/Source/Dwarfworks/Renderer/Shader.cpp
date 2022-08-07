// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Renderer/Shader.h"

#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

using namespace Dwarfworks;

Ref<Shader> Shader::Create(const std::string& filepath)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
    }
}

Ref<Shader> Shader::Create(const std::string& name, std::string& vertexSource, const std::string& fragmentSource)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
    }
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
    DW_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
}

void ShaderLibrary::Add(const Ref<Shader>& shader)
{
    auto& name = shader->GetName();
    Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
    DW_CORE_ASSERT(Exists(name), "Shader not found!");
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}
