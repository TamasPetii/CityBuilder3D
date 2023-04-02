#version 330 core

//Receiving Data
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
flat in int frag_textureID;

//Output Data
out vec4 out_color;

//Uniforms
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

uniform vec3 u_Color0;
uniform vec3 u_Color1;

uniform int u_UseTexture = 0;


void main(){
	if(frag_textureID == 0)
	{
		out_color = (u_UseTexture == 1 ? texture(u_Texture0, frag_texture) : vec4(u_Color0, 1));
	}
	else if(frag_textureID == 1)
	{ 
		out_color = (u_UseTexture == 1 ? texture(u_Texture1, frag_texture) : vec4(u_Color1, 1));
	}
	else
	{
		out_color = vec4(1, 1, 1, 1);
	}
}