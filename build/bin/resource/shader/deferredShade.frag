#version 300 es
precision highp float;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;
uniform sampler2D indirectLightTexture;
uniform sampler2D dirLitDepthTexture;

uniform vec3 ambientLightColor;
uniform vec3 directionalLightDir;
uniform vec3 directionalLightColor;
uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;
uniform float specCoefficient;

uniform mat4 viewMatrix;
uniform vec3 viewPosition;

uniform float indirectLightSwitch;
uniform float directLightSwitch;
uniform float shadowSwitch;

in vec2 texCoord;

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
    
    vec3 lightDir = normalize(-directionalLightDir);
    vec3 lightColor = max(dot(lightDir, _normal), 0.0) * directionalLightColor;
    vec3 reflectDir = reflect(-lightDir, _normal);
    lightColor += pow(max(dot(viewDir, reflectDir), 0.0), specCoefficient) * directionalLightColor;
    
    /*
    float pointLightDis = distance(pointLightPosition, basePosition.xyz);
    float attenuation = 1.0 / (1.0 + pointLightDis * 0.0001 + pointLightDis * pointLightDis * 0.0001);
    vec3 pointLightDir = normalize(pointLightPosition - basePosition.xyz);
    lightColor += max(dot(pointLightDir, _normal), 0.0) * pointLightColor * attenuation;
    vec3 pointLightReflectDir = normalize(reflect(pointLightDir, _normal));
    pointLightReflectDir = normalize(pointLightReflectDir);
    lightColor += pow(max(dot(viewDir, pointLightReflectDir), 0.0), specCoefficient) * pointLightColor *  attenuation;
    */
     
    lightColor *= max(indirectLightColor.a,  shadowSwitch);
    lightColor += ambientLightColor;
    lightColor *= directLightSwitch;
    lightColor += indirectLightColor.rgb * indirectLightSwitch;
    
    clamp(lightColor.r, 0.0, 1.0);
    clamp(lightColor.g, 0.0, 1.0);
    clamp(lightColor.b, 0.0, 1.0);
    fragColor = baseColor * vec4(lightColor, 1.0);
    //fragColor *= 0.00001;
    //fragColor.rgb += indirectLightColor.rgb;
    //fragColor.a = 1.0;
    //fragColor = baseColor * indirectLightColor.a;
    //fragColor.rgb = lightColor;
    //fragColor.rgb =  pointLightReflectDir.xyz;
    //fragColor.rgb = indirectLightColor.rgb;
    //fragColor.rgb = lightColor.rgb;
}
