#version 330 core

out vec4 frag_color;

uniform vec3 u_Color;

void main()
{
	frag_color = vec4(u_Color,1);
}