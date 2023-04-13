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

uniform vec3 u_eye;

uniform vec3 u_LightDir;
uniform int u_Specular_Pow;
uniform vec3 u_La;
uniform vec3 u_Ld;
uniform vec3 u_Ls;
uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;

vec3 CalcDirLight(vec3 light_dir, int specular_pow, vec3 La, vec3 Ld, vec3 Ls, vec3 Ka, vec3 Kd, vec3 Ks)
{
	vec3 ambient = La * Ka;

	vec3 to_light = normalize(-light_dir);
	vec3 normal = normalize(frag_normal);

	vec3 diffuse = Ld * Kd * clamp(dot(to_light,normal),0,1);

	vec3 to_eye = normalize(u_eye - frag_position);
	vec3 lr = normalize(reflect(light_dir,frag_normal));
	vec3 specular = Ls * Ks * pow(clamp(dot(lr,to_eye),0,1),specular_pow);

    return (ambient + diffuse + specular);
}

void main()
{	
	vec3 light = vec3(0, 0, 0);
	light += CalcDirLight(u_LightDir, u_Specular_Pow, u_La, u_Ld, u_Ls, u_Ka, u_Kd, u_Ks);

	if(u_UseTexture == 1)
	{
		out_color = texture(u_SpriteTexture, frag_texture * vec2(0.1, 0.1) + vec2(frag_textureID % 10 * 0.1, 0.9 - frag_textureID / 10 * 0.1)) * vec4(light, 1);
	}
	else
	{
		out_color = vec4(0,0,0,1);
	}
}