#version 330 core

	in vec3 v_Position;

    varying vec4 vColor;


	void main() {
		
	  gl_FragColor = vColor;
	}