#version 330 core
	
layout (location = 0) out vec4 color;

in vec3 v_Position;

void main() {
    vec3 finalColor = vec3(v_Position * 0.5 + 0.5);
	color = vec4(finalColor, 1.0);
}
