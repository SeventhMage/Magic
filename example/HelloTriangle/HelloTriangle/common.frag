#version 300 es
precision mediump float;
uniform sampler2D textureUnit;
uniform vec4 color;
in vec4 vOutColor;
in vec2 vTex;
out vec4 fragColor;
void main()
{
   fragColor = color * vOutColor * texture(textureUnit, vTex);
}
