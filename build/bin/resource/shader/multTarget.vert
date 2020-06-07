#version 300 es
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec4 vColor;

out vec2 texCoord;
out vec3 position;
out vec3 normal;
out vec4 color;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
void main()
{
    texCoord = vTexCoord;
    position = (modelMatrix * vec4(vPosition, 1.0)).xyz;
    mat3 normalMat = mat3(transpose(inverse(modelMatrix)));
    normal = normalMat * normalize(vNormal);
    color = vColor;
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vPosition, 1.0);
}

