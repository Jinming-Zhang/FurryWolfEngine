#version 330 core
in vec4 vertexColor;
uniform vec4 ourColor;
out vec4 finalClr;
void main()
{
  finalClr = vertexColor;
}
