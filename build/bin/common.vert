#version 300 es
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec4 vColor;
layout(location = 3) in vec3 vNormal;

out vec4 vertColor;
out vec2 texCoord;
out vec3 normal;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
void main()
{
    vertColor = vColor;
    texCoord = vTexCoord;
    mat4 mvMat = viewMatrix * modelMatrix;
    mat3 normalMat = mat3(transpose(inverse(mvMat)));
    normal = normalMat * vNormal;
    gl_Position = projMatrix * mvMat * vec4(vPosition, 1.0);
}
