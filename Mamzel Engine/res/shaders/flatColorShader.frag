# version 440 core

uniform vec4 u_Color;

uniform int u_UseTexture;
uniform sampler2D u_TexureSampler;
in vec2 v_TexCoord;

out vec4 out_color;

void main()
{
	if (u_UseTexture == 0)
		out_color = u_Color;
	else
		out_color = u_Color * texture(u_TexureSampler, v_TexCoord);
}