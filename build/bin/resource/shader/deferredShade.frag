#version 300 es
precision mediump float;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;
uniform sampler2D indirectLightTexture;

uniform vec3 ambientLightColor;
uniform vec3 directionalLightDir;
uniform vec3 directionalLightColor;
uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;
uniform float specCoefficient;

uniform mat4 viewMatrix;
uniform vec3 viewPosition;

in vec2 texCoord;
in vec3 position;

out vec4 fragColor;

void main()
{
    vec4 basePosition = texture(positionTexture, texCoord);
    vec4 baseNormal = texture(normalTexture, texCoord);
    vec4 baseColor = texture(colorTexture, texCoord);
    vec4 indirectLightColor = texture(indirectLightTexture, texCoord);
    
    vec3 _normal = normalize(baseNormal.xyz);
    vec3 viewDir = normalize(viewPosition - basePosition.xyz);
    viewDir = normalize(viewDir);
    
    vec3 lightColor = ambientLightColor;
    
    
    vec3 lightDir = normalize(-directionalLightDir);
    lightColor += max(dot(lightDir, _normal), 0.0) * directionalLightColor;
    vec3 reflectDir = reflect(lightDir, _normal);
    lightColor += pow(max(dot(viewDir, reflectDir), 0.0), specCoefficient) * directionalLightColor;
    
    
    float pointLightDis = distance(pointLightPosition, basePosition.xyz);
    float attenuation = 1.0 / (1.0 + pointLightDis * 0.001 + pointLightDis * pointLightDis * 0.0001);
    vec3 pointLightDir = normalize(pointLightPosition - basePosition.xyz);
    lightColor += max(dot(pointLightDir, _normal), 0.0) * pointLightColor * attenuation;
    vec3 pointLightReflectDir = normalize(reflect(pointLightDir, _normal));
    pointLightReflectDir = normalize(pointLightReflectDir);
    lightColor += pow(max(dot(viewDir, pointLightReflectDir), 0.0), specCoefficient) * pointLightColor *  attenuation;
     
    lightColor += indirectLightColor.rgb;
    lightColor *= indirectLightColor.a;
    clamp(lightColor.r, 0.0, 1.0);
    clamp(lightColor.g, 0.0, 1.0);
    clamp(lightColor.b, 0.0, 1.0);
    fragColor = baseColor * vec4(lightColor, 1.0);
    //viewDir = normalize(viewDir);
//    if (viewDir.x > 1.0 || viewDir.z > 1.0 || viewDir.y > 1.0)
//        fragColor.rgb = vec3(len, len, len);
//    else
//        fragColor.rgb = vec3(0, 0, 0);
    //fragColor.rgb =  pointLightReflectDir.xyz;
    //fragColor.rgb = indirectLightColor.rgb;
    //fragColor.rgb = lightColor.rgb;
}
