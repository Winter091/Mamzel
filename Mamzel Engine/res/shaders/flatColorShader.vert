#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_MatrixMVP;
uniform float u_TextureRepeatCount;

out vec2 v_TexCoord;

void main() 
{
	gl_Position = u_MatrixMVP * vec4(a_Pos, 1.0);
	v_TexCoord = a_TexCoord * u_TextureRepeatCount;
}