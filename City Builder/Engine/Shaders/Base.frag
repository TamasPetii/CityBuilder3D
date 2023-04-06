#version 330 core

//Receiving Data
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
flat in int frag_textureID;

//Output Data
out vec4 out_color;

//Uniforms
uniform vec3 u_color;

void main()
{	
	out_color = vec4(u_color, 1);
}