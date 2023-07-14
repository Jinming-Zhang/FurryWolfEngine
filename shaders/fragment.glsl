#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
uniform vec4 ourColor;
out vec4 finalClr;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixPct;

void main()
{
  // finalClr = mix(texture(texture1, texCoord),texture(texture2, texCoord),.5f) *  (ourColor+vertexColor);
  // finalClr = texture(texture1, texCoord);
  finalClr = mix(texture(texture1, texCoord),texture(texture2, vec2(texCoord.x, texCoord.y)),mixPct);
}
