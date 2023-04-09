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

void main()
{	
	if(u_UseTexture == 1)
	{
		out_color = texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + vec2(frag_textureID % 10 * 0.1, 0.9 - frag_textureID / 10 * 0.1));
	}
	else
	{
		out_color = vec4(0,0,0,1);
	}
}