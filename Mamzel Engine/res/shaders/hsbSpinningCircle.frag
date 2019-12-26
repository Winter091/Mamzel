# version 440 core

uniform vec2 u_Resolution;
uniform float u_Time;

out vec4 out_color;

vec3 hsb2rgb(in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

#define PI 3.1415926

void main()
{
	vec2 pos = gl_FragCoord.xy / u_Resolution;
	vec2 posToCenter = 0.5 - pos;

	// Multiply by rotation matrix
	float x = cos(u_Time) * posToCenter.x - sin(u_Time) * posToCenter.y;
	float y = sin(u_Time) * posToCenter.x + cos(u_Time) * posToCenter.y;

	float angle = atan(y, x);
	float radius = length(posToCenter) * 2.0;

	// from [-PI, PI] to [0, 1]
	angle = angle / (2 * PI) + 0.5;

	vec3 color = hsb2rgb(vec3(angle, radius, 1.0));
	
	out_color = vec4(color, 1.0);
}