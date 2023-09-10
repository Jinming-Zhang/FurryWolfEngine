#version 330 core
out vec4 finalClr;

struct Material {
  int albedoMapsCount;
  sampler2D albedoMap0;
  sampler2D albedoMap1;
  sampler2D albedoMap2;
  sampler2D normalMap;
  int specularMapsCount;
  sampler2D specularMap0;
  sampler2D specularMap1;
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

struct PointLight {
  Light baseLight;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

struct SpotLight {
  PointLight basePtLight;
  vec3 direction;
  float innerCutoffAngle;
  float outterCutoffAngle;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform vec3 eyePos;

uniform vec3 baseColor;
uniform Material material;
uniform DirectionalLight dLight;

#define MAX_POINT_LIGHTS 4
uniform int pLightsCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
#define MAX_SPOT_LIGHTS 4
uniform int spLightsCount;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec3 calcLightColor(Light baseLight, vec3 direction, float attenuation);
vec3 calcLightColor(Light baseLight,
                    vec3 direction); // default attenuation to 1.0f
vec3 calcDirectionalLight();
vec3 calcPointLight(PointLight ptLight);
vec3 calcSpotLight(SpotLight spLight);

void main() {
  // directional light
  vec3 dLightColor = calcDirectionalLight();
  // point lights
  vec3 pLightsColor = vec3(0.0f);
  for (int i = 0; i < pLightsCount; ++i) {
    pLightsColor += calcPointLight(pointLights[i]);
  }
  // spot lights
  vec3 spLightsColor = vec3(0.0f);
  for (int i = 0; i < spLightsCount; ++i) {
    spLightsColor += calcSpotLight(spotLights[i]);
  }

  finalClr = vec4(dLightColor + pLightsColor + spLightsColor, 1.0f);
}

vec3 calcLightColor(Light baseLight, vec3 direction, float attenuation) {
  vec3 texColor = vec3(0.0f);
  texColor += vec3(texture(material.albedoMap0, texCoord));
  if (material.albedoMapsCount >= 2) {
    texColor += vec3(texture(material.albedoMap1, texCoord));
  }
  if (material.albedoMapsCount >= 3) {
    texColor += vec3(texture(material.albedoMap2, texCoord));
  }
  vec3 specu = vec3(.0f);
  specu += vec3(texture(material.specularMap0, texCoord));
  if (material.specularMapsCount >= 2) {
    specu += vec3(texture(material.specularMap1, texCoord));
  }

  vec3 objAmbient = texColor*baseColor;
  vec3 objDiffuse = texColor;
  vec3 objSpecular = specu * texColor;

  // ambient color
  vec3 ambientColor = baseLight.ambient * objAmbient * attenuation;

  // diffuse color
  vec3 norm = normalize(normal);
  vec3 lightDirToLightSource = normalize(-direction);
  float diffuseFactor = max(0.0, dot(norm, lightDirToLightSource));
  vec3 diffuseColor =
      baseLight.diffuse * objDiffuse * diffuseFactor * attenuation;

  // specular color
  vec3 viewDir = normalize(eyePos - fragPos);
  vec3 reflectDir = reflect(-lightDirToLightSource, norm);
  float specularFactor = max(0.0, dot(reflectDir, viewDir));
  specularFactor = pow(specularFactor, material.shininess);
  vec3 specularColor =
      baseLight.specular * objSpecular * specularFactor * attenuation;

  return ambientColor + diffuseColor + specularColor;
}

vec3 calcLightColor(Light baseLight, vec3 direction) {
  return calcLightColor(baseLight, direction, 1.0f);
}

vec3 calcDirectionalLight() {
  return calcLightColor(dLight.baseLight, dLight.direction);
}

vec3 calcPointLight(PointLight ptLight) {
  vec3 direction = fragPos - ptLight.position;
  float dst = length(direction);
  float attenuation = 1.0f / (ptLight.constant + ptLight.linear * dst +
                              ptLight.quadratic * pow(dst, 2));
  vec3 lightColor = calcLightColor(ptLight.baseLight, direction, attenuation);

  return lightColor;
}

vec3 calcSpotLight(SpotLight spLight) {
  vec3 lightToFragDir = fragPos - spLight.basePtLight.position;
  lightToFragDir = normalize(lightToFragDir);
  vec3 lightDir = normalize(spLight.direction);

  float theta = dot(lightToFragDir, lightDir);
  float epsilon = spLight.innerCutoffAngle - spLight.outterCutoffAngle;
  float intensity =
      clamp((theta - spLight.outterCutoffAngle) / epsilon, .0f, 1.0f);
  vec3 lightColor = intensity * calcPointLight(spLight.basePtLight);
  return lightColor;
}
