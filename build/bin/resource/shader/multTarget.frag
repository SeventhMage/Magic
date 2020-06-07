#version 300 es
precision mediump float;
uniform sampler2D textureUnit;
uniform vec4 _color;

in vec2 texCoord;
in vec4 color;
in vec3 normal;
in vec3 position;

layout(location = 0) out vec4 fragPosition;
layout(location = 1) out vec4 fragNormal;
layout(location = 2) out vec4 fragColor;

void main()
{
    fragPosition = vec4(position, 1.0);
    fragNormal = vec4(normalize(normal), 1.0);
    fragColor = texture(textureUnit, texCoord) * _color;
    fragColor = _color;
}
