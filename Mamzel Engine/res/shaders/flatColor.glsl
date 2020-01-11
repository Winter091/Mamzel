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

uniform int u_UseTexture;
uniform sampler2D u_TextureSampler;
in vec2 v_TexCoord;

out vec4 out_color;

void main()
{
	if (u_UseTexture == 0)
		out_color = u_ObjectColor;
	else
		out_color = u_ObjectColor * texture(u_TextureSampler, v_TexCoord);
}