# version 440 core

uniform vec2 u_Resolution;
uniform float u_Time;

out vec4 out_color;

float rect(vec2 pos, float w, float h, float smoothness)
{	
	float xBorderLeft = 0.5 - w / 2 - smoothness;
	float yBorderLeft = 0.5 - h / 2 - smoothness;
	float xBorderRight = 0.5 - w / 2 + smoothness;
	float yBorderRight = 0.5 - h / 2 + smoothness;

	vec2 start = vec2(xBorderLeft, yBorderLeft);
	vec2 end = vec2(xBorderRight, yBorderRight);
	
	vec2 bl = smoothstep(start, end, pos);
	vec2 tr = smoothstep(start, end, 1.0 - pos);

	return bl.x * bl.y * tr.x * tr.y;
}

float rectMove(vec2 pos, float x, float y, float w, float h, float smoothness)
{	
	float xBorderLeft = 0.5 - w / 2 - smoothness;
	float yBorderLeft = 0.5 - h / 2 - smoothness;
	float xBorderRight = 0.5 - w / 2 + smoothness;
	float yBorderRight = 0.5 - h / 2 + smoothness;

	vec2 start = vec2(xBorderLeft, yBorderLeft);
	vec2 end = vec2(xBorderRight, yBorderRight);
	
	//vec2 bl = smoothstep(start + vec2(x, y), end + vec2(x, y), pos);
	//vec2 tr = smoothstep(start - vec2(x, y), end - vec2(x, y), 1.0 - pos);

	vec2 bl = smoothstep(start, end, pos - vec2(x, y));
	vec2 tr = smoothstep(start, end, 1.0 - pos + vec2(x, y));

	return bl.x * bl.y * tr.x * tr.y;
}

float rectOutline(vec2 pos, float w, float h, float thickness)
{
	vec2 outerbl = step(vec2(0.5 - w / 2 - thickness / 2, 0.5 - h / 2 - thickness / 2), pos);
	vec2 outertr = step(vec2(0.5 - w / 2 - thickness / 2, 0.5 - h / 2 - thickness / 2), 1.0 - pos);

	vec2 innerbl = step(vec2(0.5 - w / 2 + thickness / 2, 0.5 - h / 2 + thickness / 2), pos);
	vec2 innertr = step(vec2(0.5 - w / 2 + thickness / 2, 0.5 - h / 2 + thickness / 2), 1.0 - pos);

	return (outerbl.x * outerbl.y * outertr.x * outertr.y) - (innerbl.x * innerbl.y * innertr.x * innertr.y);
}

void main()
{
	vec2 pos = gl_FragCoord.xy / u_Resolution.xy;
	
	vec3 color = vec3(242, 234, 214) / 255;
	color = mix(color, vec3(168, 33,   37) / 255.0, rectMove(pos, -0.39, 0.33, 0.22, 0.34, 0));
	color = mix(color, vec3(251, 194,  49) / 255.0, rectMove(pos,  0.48, 0.33, 0.04, 0.34, 0));
	color = mix(color, vec3(0,   94,  155) / 255.0, rectMove(pos,  0.38,-0.45, 0.24, 0.11, 0));
	
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos, -0.27, 0.0, 0.025, 1.0, 0));
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos,  0.45, 0.0, 0.025, 1.0, 0));
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos,  0.25, 0.0, 0.025, 1.0, 0));
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos, -0.42, 0.33, 0.025, 0.34, 0));

	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos, 0.0, 0.33, 1.0, 0.03, 0));
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos, 0.0, 0.15, 1.0, 0.03, 0));
	color = mix(color, vec3(21, 22, 27) / 255.0, rectMove(pos, 0.12,-0.38, 0.77, 0.03, 0));
	
	out_color = vec4(color, 1.0);
}

