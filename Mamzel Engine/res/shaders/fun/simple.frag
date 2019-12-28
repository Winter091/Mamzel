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

float circle(vec2 pos, float x, float y, float r)
{
	float distToCenterSqr = dot(vec2(pos.x - x, pos.y - y), vec2(pos.x - x, pos.y - y));
	return 1.0 - smoothstep(r * (r - 0.002), r * (r + 0.002),  distToCenterSqr);
}

void main()
{
	vec2 pos = gl_FragCoord.xy / u_Resolution.xy;
	pos = pos * 2.0 - 1.0;

	float d = length( max(abs(pos) - 0.3, vec2(0.0)) );

	vec3 color = vec3(d);
	//color.r *= abs(tan(u_Time + 3.14 / 3));
	//color.g *= abs(tan(u_Time + 3.14 / 3 * 2));
	//color.b *= abs(tan(u_Time + 3.14 / 3 * 3));

	out_color = vec4(color, 1.0);
}

