#version 330 core
	
layout (location = 0) in vec3 a_Position;

out vec3 v_Position;
out vec4 vColor;
    
void main() {
	v_Position = vec3(a_Position.x, a_Position.y, a_Position.z);
    vColor = vec4(a_Position, 1.0);
	gl_Position = vec4(a_Position, 1.0);
}
