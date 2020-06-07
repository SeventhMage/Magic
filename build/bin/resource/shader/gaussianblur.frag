#version 300 es
precision mediump float;

uniform sampler2D textureColor;
uniform vec4 uKernel[15];

in vec2 texCoord;
out vec4 fragColor;

void main()
{
	vec4 c = vec4(0.0, 0.0, 0.0, 0.0);
	for (int u=0; u<15; ++u)
	{
		vec3 v = uKernel[u].xyz;
		c += texture(textureColor, texCoord + v.xy).xyzw * v.z;
	}
	fragColor = c;
}