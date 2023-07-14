#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
uniform vec4 ourColor;
out vec4 finalClr;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixPct;

void main()
{
  finalClr = mix(texture(texture0, texCoord),texture(texture1, texCoord),.5f) *  (ourColor+vertexColor);

  finalClr = mix(texture(texture0, texCoord),texture(texture1, texCoord),mixPct) *  (ourColor+vertexColor);

  finalClr = mix(texture(texture0, texCoord),texture(texture1, vec2(texCoord.x, texCoord.y)),mixPct);
}
