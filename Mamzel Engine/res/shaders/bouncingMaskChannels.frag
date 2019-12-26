# version 440 core

uniform vec2 u_Resolution;
uniform float u_Time;

out vec4 out_color;

float Plot(float x, float y)
{
	return smoothstep(x - 0.01, x, y) - 
		   smoothstep(x, x + 0.01, y);
}

void main()
{
	vec2 pos = gl_FragCoord.xy / u_Resolution;

	//vec3 colorA = vec3(0.149, 0.141, 0.912);
	//vec3 colorB = vec3(1.000, 0.833, 0.224);

	vec3 mask = vec3(pos.x);
	mask.r = smoothstep(0.0, 1.0, (1.0 - mask.r) * abs(cos(u_Time / 1.235)));
	mask.g = sin(mask.g * 3.1415) * abs(sin(u_Time));
	mask.b = pow(mask.b, 0.5) * (1 - abs(cos(u_Time / 1.78)));

	vec3 color = vec3(1.0) * mask;

	color = mix(color, vec3(1.0, 0.0, 0.0), Plot(mask.r, pos.y));
	color = mix(color, vec3(0.0, 1.0, 0.0), Plot(mask.g, pos.y));
	color = mix(color, vec3(0.0, 0.0, 1.0), Plot(mask.b, pos.y));

	out_color = vec4(color, 1.0);
}