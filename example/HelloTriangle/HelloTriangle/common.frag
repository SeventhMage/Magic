#version 300 es
precision mediump float;
uniform sampler2D textureUnit;
uniform vec4 color;
uniform vec3 ambientLightColor;
uniform vec3 directionalLightDir;
uniform vec3 directionalLightColor;
uniform vec3 viewDir;
uniform float specCoefficient;

in vec4 vertColor;
in vec2 texCoord;
in vec3 normal;
out vec4 fragColor;

void main()
{
    vec3 lightColor = ambientLightColor;
    vec3 dir = normalize(directionalLightDir);
    vec3 _normal = normalize(normal);
    lightColor += max(dot(dir, _normal), 0.0) * directionalLightColor;
    vec3 reflectDir = reflect(-dir, _normal);
    lightColor += pow(max(dot(viewDir, reflectDir), 0.0), specCoefficient) * directionalLightColor;
    fragColor = color * vertColor * vec4(lightColor, 1.0) * texture(textureUnit, texCoord);
}
