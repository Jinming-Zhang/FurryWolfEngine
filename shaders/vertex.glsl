#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aClr;
layout (location=2) in vec2 aTexCoord;
layout (location=3) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
  gl_Position =  cameraMatrix * model * vec4(aPos, 1.0);
  fragPos = vec3(model*vec4(aPos,1.f));
  texCoord = aTexCoord;
  normal = mat3(transpose(inverse(model))) * aNormal;  
}
