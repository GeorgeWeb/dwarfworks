#type vertex
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

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
   
in vec4 v_Color;

void main()
{
	color = v_Color;
}
