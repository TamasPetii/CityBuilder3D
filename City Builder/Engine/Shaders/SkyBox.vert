#version 330 core

//Receiving Data
layout(location = 0) in vec3 vert_position;

//Output Data
out vec3 frag_position;

//Uniforms
uniform mat4 u_VP;
uniform mat4 u_M;

void main(){
	gl_Position = (u_VP * u_M * vec4(vert_position, 1)).xyww;

	frag_position = vert_position;
}