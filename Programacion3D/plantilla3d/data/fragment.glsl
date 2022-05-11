uniform sampler2D texSampler;
uniform int hasTex;
varying vec2 ftex;

void main()
{
if(fhasTex == 1)
{
gl_FragColor = texture2D(texSampler, ftex);
}
else
{
gl_FragColor = vec4(1,1,1,1);
}
}