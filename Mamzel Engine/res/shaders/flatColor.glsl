#VERTEX SHADER

#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_MatrixMVP;
uniform float u_TextureScale;

out vec2 v_TexCoord;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
	v_TexCoord = a_TexCoord * u_TextureScale;
}

#FRAGMENT SHADER

# version 440 core

uniform vec4 u_ObjectColor;

uniform bool u_UseDiffuseTexture;
uniform bool u_UseSpecularTexture = false;
uniform sampler2D u_DiffuseTextureSampler;
uniform sampler2D u_SpecularTextureSampler;
in vec2 v_TexCoord;

out vec4 out_color;

void main()
{
	out_color = u_ObjectColor;

	if (u_UseDiffuseTexture)
		out_color *= texture(u_DiffuseTextureSampler, v_TexCoord);

	if (u_UseSpecularTexture)
		out_color += texture(u_SpecularTextureSampler, v_TexCoord) * 0.1;

	out_color.a = 1.0;
}