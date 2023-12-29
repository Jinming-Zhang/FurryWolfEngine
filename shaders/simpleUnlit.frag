#version 330 core
in vec2 texCoord;
out vec4 FragColor;

struct Material {
  int albedoMapsCount;
  sampler2D albedoMap0;
  sampler2D albedoMap1;
  sampler2D albedoMap2;
};

uniform vec3 baseColor;
uniform Material material;
uniform bool opaque;
uniform float transparency;

void main() {
  vec4 color4 = vec4(baseColor, transparency);
  if (material.albedoMapsCount >= 1) {
    color4 *= texture(material.albedoMap0, texCoord);
  }
  if (material.albedoMapsCount >= 2) {
    color4 *= texture(material.albedoMap1, texCoord);
  }
  if (material.albedoMapsCount >= 3) {
    color4 *= texture(material.albedoMap2, texCoord);
  }
  color4.a=transparency;
 // if (!opaque) {
//    if (color4.a < 0.1) {
    //  discard;
   // }
  //}
  FragColor = color4;
}
