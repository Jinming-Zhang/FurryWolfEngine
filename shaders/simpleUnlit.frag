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

void main() {
  vec3 color3 = baseColor;
  if (material.albedoMapsCount >= 1) {
    color3 *= texture(material.albedoMap0, texCoord).rgb;
  }
  if (material.albedoMapsCount >= 2) {
    color3 *= texture(material.albedoMap1, texCoord).rgb;
  }
  if (material.albedoMapsCount >= 3) {
    color3 *= texture(material.albedoMap2, texCoord).rgb;
  }
  FragColor = vec4(color3, 1.0);
}
