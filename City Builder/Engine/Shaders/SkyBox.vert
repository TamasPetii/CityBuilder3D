#version 330 core

//Receiving Data
layout(location = 0) in vec3 vert_position;

//Output Data
out vec3 frag_position;

//Uniforms
uniform mat4 u_MVP;

void main(){
	gl_Position = (u_MVP * vec4(vert_position, 1)).xyww;

	frag_position = vert_position;
}