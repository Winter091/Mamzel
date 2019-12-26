# version 440 core

uniform vec2 u_resolution;
uniform vec2 u_translation;
uniform vec4 u_color;

uniform float u_realCoeff;
uniform float u_imagCoeff;
uniform float u_divideCoeff;

in vec2 v_Coord;
out vec4 out_color;

void main()
{
	vec2 pos = v_Coord + u_translation;
	pos = pos * 3.0 - 1.5;

	float real = pos.x;
	float imag = pos.y;

	out_color = vec4(vec3(0.0), 1.0) * u_color;

	for (float i = 0; i < 200; i++)
	{
		float realTemp = real;
		real = real * real - imag * imag + u_realCoeff;
		imag = 2 * realTemp * imag + u_imagCoeff;
		if (real * real + imag * imag > 16)
		{
			out_color = vec4(vec3(i / u_divideCoeff), 1.0) * u_color;
		}
	}
}

