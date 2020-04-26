#version 300 es
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec4 vColor;
out vec4 vOutColor;
out vec2 vTex;
uniform mat4 vpMatrix;
uniform mat4 mMatrix;
void main()
{
    vOutColor = vColor;
    vTex = vTexCoord;
    gl_Position = vpMatrix * mMatrix * vec4(vPosition, 1.0);
}
