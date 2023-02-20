#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 g_position;
out vec3 g_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);

  g_position = vec3(model * vec4(position, 1.0));
  g_normal   = transpose(inverse(mat3(model))) * normal;
}