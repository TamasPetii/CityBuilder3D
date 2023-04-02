#version 330 core

//Receiving Data
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
flat in int frag_textureID;

//Output Data
out vec4 out_color;

//Uniforms
uniform sampler2D u_SpriteTexture;
uniform int  u_UseTexture = 0;
uniform vec2 u_TextureCoords0;
uniform vec2 u_TextureCoords1;
uniform vec2 u_TextureCoords2;
uniform vec2 u_TextureCoords3;
uniform vec2 u_TextureCoords4;
uniform vec2 u_TextureCoords5;

uniform vec3 u_Color0;
uniform vec3 u_Color1;
uniform vec3 u_Color2;
uniform vec3 u_Color3;
uniform vec3 u_Color4;
uniform vec3 u_Color5;

void main()
{	
	if(frag_textureID == 0)
	{
		out_color = (u_UseTexture == 1 ? texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + u_TextureCoords0) : vec4(u_Color0, 1));
	}
	else if(frag_textureID == 1)
	{ 
		out_color = (u_UseTexture == 1 ? texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + u_TextureCoords1) : vec4(u_Color1, 1));
	}
	else if(frag_textureID == 2)
	{
		out_color = (u_UseTexture == 1 ? texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + u_TextureCoords2) : vec4(u_Color2, 1));
	}
	else
	{
		out_color = vec4(1, 1, 1, 1);
	}
}