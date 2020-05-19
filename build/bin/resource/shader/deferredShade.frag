#version 300 es
precision mediump float;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;
uniform sampler2D indirectLightTexture;

uniform mat4 viewMatrix;
uniform vec3 ambientLightColor;
uniform vec3 directionalLightDir;
uniform vec3 directionalLightColor;
uniform float specCoefficient;

in vec2 texCoord;
in vec3 position;

out vec4 fragColor;

void main()
{
    vec4 basePosition = texture(positionTexture, texCoord);
    vec4 baseNormal = texture(normalTexture, texCoord);
    vec4 baseColor = texture(colorTexture, texCoord);
    vec4 indirectLightColor = texture(indirectLightTexture, texCoord);
    
    vec3 lightDir = normalize(viewMatrix * vec4(directionalLightDir, 1.0)).xyz;
    vec3 lightColor = ambientLightColor;
    vec3 _normal = normalize(baseNormal.xyz);
    lightColor += max(dot(lightDir, _normal), 0.0) * directionalLightColor;
    vec3 reflectDir = reflect(-lightDir, _normal);
    lightColor += pow(max(dot(vec3(0.0, 0.0, -1.0), reflectDir), 0.0), specCoefficient) * directionalLightColor;
    fragColor = baseColor * vec4(lightColor + indirectLightColor.rgb, 1.0);
    fragColor.rgb = indirectLightColor.rgb;
}
