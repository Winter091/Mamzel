# version 440 core

in vec2 v_Color;
out vec4 out_color;

void main()
{
	out_color = vec4(v_Color, 0.0, 1.0);
}

