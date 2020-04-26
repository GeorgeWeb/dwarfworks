// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Graphics/Shader.h"

#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dwarfworks {

Ref<Shader> Shader::Create(std::string_view filepath) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			DW_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);
	}

	DW_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<Shader> Shader::Create(std::string_view vertexSource, std::string_view fragmentSource) {
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

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
	DW_CORE_ASSERT(!Exists(name), "Shader already exists!");
	m_Shaders[name] = shader;
}

void ShaderLibrary::Add(const Ref<Shader>& shader) {
	auto& name = shader->GetName();
	Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
	auto shader = Shader::Create(filepath);
	Add(shader);
	return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
	auto shader = Shader::Create(filepath);
	Add(name, shader);
	return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name) {
	DW_CORE_ASSERT(Exists(name), "Shader not found!");
	return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const {
	return m_Shaders.find(name) != m_Shaders.end();
}

}  // namespace Dwarfworks
