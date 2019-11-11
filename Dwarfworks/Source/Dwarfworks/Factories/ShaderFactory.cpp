// begin PCH
#include "dwpch.h"
// end PCH

#include "ShaderFactory.h"

namespace Dwarfworks {

// ------------------------------------------ //
// -- Flat Color Shader --------------------- //
// ------------------------------------------ //

static const char* const s_FlatColorShaderVS = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	void main()
	{
	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
  )";

static const char* const s_FlatColorShaderFS = R"(
	#version 330 core

	layout(location = 0) out vec4 color;

	uniform vec3 u_Color;

	void main()
	{
	  color = vec4(u_Color, 1.0);
	}
  )";

Ref<Shader> ShaderFactory::FlatColorShader() {
  return Shader::Create(s_FlatColorShaderVS, s_FlatColorShaderFS);
}

// ------------------------------------------ //
// -- Vertex Color Gradient Shader ---------- //
// ------------------------------------------ //

static const char* const s_VertexColorGradientShaderVS = R"(
	#version 330 core

	layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	out vec4 v_Color;

	void main() {
	  v_Color = a_Color;

	  vec4 vertexPosition = vec4(a_Position, 1.0);
	  gl_Position = u_ViewProjection * u_Transform * vertexPosition;
	}
  )";

static const char* const s_VertexColorGradientShaderFS = R"(
	#version 330 core

	layout(location = 0) out vec4 color;
   
	in vec4 v_Color;

	void main()
	{
	  color = v_Color;
	}
  )";

Ref<Shader> ShaderFactory::VertexColorGradientShader() {
  return Shader::Create(s_VertexColorGradientShaderVS, s_VertexColorGradientShaderFS);
}

}
