#version 330 core
out vec4 finalClr;

struct Material{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light{
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixPct;


uniform vec3 eyePos;
uniform Material material;
uniform Light light;

void main()
{
  // finalClr = mix(texture(texture0, texCoord),texture(texture1, texCoord),.5f) *  (ourColor+vertexColor);

  // finalClr = mix(texture(texture0, texCoord),texture(texture1, texCoord),mixPct) *  (ourColor+vertexColor);

  // finalClr = mix(texture(texture0, texCoord),texture(texture1, vec2(texCoord.x, texCoord.y)),mixPct);

  // ambient
  vec3 ambient = light.ambient*material.ambient;

  // diffuse
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(light.position-fragPos);
  float diffuse = max(dot(norm, lightDir),0.0);
  vec3 diffuseColor = light.diffuse * diffuse * material.diffuse;

  // specular
  vec3 viewDir = normalize(eyePos-fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), .0f), material.shininess);
  vec3 specular = spec * light.specular * material.specular;
  finalClr = vec4(ambient+diffuseColor+specular, 1.f);
}
