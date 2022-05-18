#version 430

in vec4 varyingColor;
in vec2 ftex;
uniform sampler2D texSampler;

void main()
{
gl_FragColor = texture2D(texSampler, ftex) * varyingColor;
}