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
uniform sampler2D u_SpriteTexture;

void main()
{	
	out_color = vec4(u_color, 1) * texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + vec2(frag_textureID % 10 * 0.1, 0.9 - frag_textureID / 10 * 0.1));
}