#version 330 core

//Receiving Data
in vec3 frag_position;

//Output Data
out vec4 out_color;

//Uniforms
uniform samplerCube u_textureMap;

void main(){
	out_color = texture(u_textureMap, frag_position);
}