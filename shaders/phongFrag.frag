#version 330 core
out vec4 finalClr;

struct Material {
  sampler2D albedoMap;
  sampler2D normalMap;
  sampler2D specularMap;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct DirectionalLight {
  Light baseLight;
  vec3 direction;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture1;
uniform float mixPct;

uniform vec3 eyePos;
uniform Material material;
uniform DirectionalLight dLight;

vec4 calcDirectionalLight() {
  vec3 texColor = vec3(texture(material.albedoMap, texCoord));
  vec3 specu = vec3(texture(material.specularMap, texCoord));
  vec3 objAmbient = texColor;
  vec3 objDiffuse = texColor;
  vec3 objSpecular = specu * texColor * 3;

  // ambient
  vec3 ambient = dLight.baseLight.ambient * objAmbient;

  // diffuse
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(-dLight.direction);
  float diffuse = max(dot(norm, lightDir), 0.0);
  vec3 diffuseColor = dLight.baseLight.diffuse * diffuse * objDiffuse;

  // specular
  vec3 viewDir = normalize(eyePos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), .0f), material.shininess);
  vec3 specular = spec * dLight.baseLight.specular * objSpecular;

  return vec4(ambient + diffuseColor + specular, 1.f);
}
void main() {
  vec4 dLightColor = calcDirectionalLight();
  finalClr = dLightColor;
}
