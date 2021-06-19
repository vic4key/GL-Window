#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

void main()
{
  color = vec4(abs(normal), 1.0);
  mat4 mvp = projection * view * model;
  gl_Position = mvp * vec4(pos, 1);
}