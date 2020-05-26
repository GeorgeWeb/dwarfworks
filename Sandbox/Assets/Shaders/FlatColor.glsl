#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	vec4 vertexPosition = vec4(a_Position, 1.0);
	gl_Position = u_ViewProjection * u_Transform * vertexPosition;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = vec4(u_Color);
}
